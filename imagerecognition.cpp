#include "imagerecognition.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

ImageRecognition::ImageRecognition()
{

}


cv::Mat QImageToMat(QImage &image)
{
    // 确保QImage是RGB32或格式正确的图像
    if (image.format() == QImage::Format_RGB32 || image.format() == QImage::Format_ARGB32)
    {
        // 使用QImage的bits()方法获取指向图像数据的指针
        uchar *data = image.bits();
        // 创建一个cv::Mat对象, 数据指针与QImage共享
        cv::Mat mat(image.height(), image.width(), CV_8UC4, data);
        // 返回OpenCV格式的Mat图像
        return mat.clone(); // 使用clone确保独立内存
    }
    else
    {
        // 如果QImage的格式不是RGB32，则需要转换
        QImage convertedImage = image.convertToFormat(QImage::Format_RGB888);
        // 将QImage转换为OpenCV的Mat对象
        cv::Mat mat(convertedImage.height(), convertedImage.width(), CV_8UC3, convertedImage.bits());
        // 返回OpenCV格式的Mat图像
        return mat.clone(); // 使用clone确保独立内存
    }
}

void ImageRecognition::recogniton(QImage image, std::vector<std::vector<Piece> > &boarder)
{
    //读取棋盘
    Mat img = QImageToMat(image);  // 转换为cv::Mat
    // 转换为灰度图像
    Mat gray;
    cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    // 高斯模糊
    GaussianBlur(gray, gray, cv::Size(5, 5), 0);
    // 边缘检测
    Mat edges;
    Canny(gray, edges, 50, 100, 3, false);

    // 轮廓提取
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 找到最大的轮廓，即棋盘的轮廓
    vector<Point> maxContour;
    double maxArea = 0;
    for (int i = 0;i<contours.size();i++)
    {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxContour = contours[i];
        }
    }

    // 找到棋盘的四个角点
    RotatedRect rect = minAreaRect(maxContour);

    // 找到棋盘上的棋子
    vector<Vec3f> circles;
    HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, 20, 100, 19, 10, 20);

    // 计算棋盘的大小
    int width = static_cast<int>(rect.size.width);
    int height = static_cast<int>(rect.size.height);
    cout << width << " " << height<<endl;
    // 计算每个圆形所在的格子位置（这块需要根据实际摄像头传回的数据进行修正）
    vector<vector<int> > centers; // 存储圆心坐标和格子位置
    int r;
    for (const auto& center : circles) {
        int cx = center[0];
        int cy = center[1];
        r = center[2];
        // 计算格子行号和列号，从0开始
        int row = static_cast<int>(cy / (width / 18));
        int col = static_cast<int>(cx / (height / 18));
        // 添加到vector中
        std::vector<int> v1 = { cx,cy,row,col };
        centers.push_back(v1);
    }

    // 颜色空间转换，将图像转换为HSV空间
    Mat hsv;
    cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    // 阈值分割，根据黑子和白子的颜色范围分别设置阈值，得到两个二值图像
    Mat mask_black, mask_white;
    inRange(hsv, cv::Scalar(0, 0, 10), cv::Scalar(180, 255, 90), mask_black);
    inRange(hsv, cv::Scalar(0, 0, 100), cv::Scalar(180, 30, 255), mask_white);

    // 与运算，将二值图像和原图像相与，得到黑子和白子的图像
    Mat res_black, res_white;
    bitwise_and(img, img, res_black, mask_black);
    bitwise_and(img, img, res_white, mask_white);
    cvtColor(res_black, res_black, cv::COLOR_BGR2GRAY);
    cvtColor(res_white, res_white, cv::COLOR_BGR2GRAY);

    // 统计每个圆形区域内的非零像素个数，判断是否有棋子，以及棋子的颜色
    vector<pair<string, Point>> stones; // 存储棋子的颜色和位置
    for (const auto& center : centers) {
        int cx = center[0];
        int cy = center[1];
        int row = center[2];
        int col = center[3];
        // 在黑子图像上取一个圆形区域
        Mat black_roi = res_black(Rect(cx - r, cy - r, 2 * r, 2 * r));
        // 计算非零像素个数
        int nz_count_black = countNonZero(black_roi);
        // 如果大于阈值，则判断为黑子
        if (nz_count_black > 50) {
            Point p;
            p.x = row;
            p.y = col;
            stones.emplace_back("black", p);
            continue;
        }
        // 在白子图像上取一个圆形区域
        Mat white_roi = res_white(Rect(cx - r, cy - r, 2 * r, 2 * r));
        // 计算非零像素个数
        int nz_count_white = countNonZero(white_roi);
        // 如果大于阈值，则判断为白子
        if (nz_count_white > 50) {
            Point p;
            p.x = row;
            p.y = col;
            stones.emplace_back("white", p);
            continue;
        }
    }

    // 输出棋子的颜色和位置信息
    vector<vector<Piece>> board(19, vector<Piece>(19));
    for (const auto& stone : stones) {
        string color = stone.first;
        Point pos = stone.second;
        int row = pos.x;
        int col = pos.y;
        cout << "There is a " << color << " stone at row " << row+1<< " and column " << col+1<< "." << endl;
        board[row][col].color = (color == "white") ? 1 : 0;
    }
    boarder = board;
}
















//



// 将数字转换为大写字母
string getChar(int number) {
    int factor, moder;
    factor = number / 26;
    moder = number % 26;
    char modChar = 'A' + moder;
    if (factor != 0) {
        modChar = getChar(factor - 1)[0] + modChar; // factor - 1: 商为有效值时起始数为 1 而余数是 0
    }
    return string(1, modChar);
}

vector<string> getChars(int length) {
    vector<string> chars;
    for (int i = 0; i < length; i++) {
        chars.push_back(getChar(i));
    }
    return chars;
}

// 计算二值化图片黑色像素点百分比
double Heise_zhanbi(const Mat& img) {
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    int black_pixels = countNonZero(gray < 125);
    double zhanbi = (double) black_pixels / (img.rows * img.cols);

    return zhanbi;
}

// 计算二值化图片白色像素点百分比
double Baise_zhanbi(const Mat& img) {
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    int white_pixels = countNonZero(gray > 235);
    double zhanbi = (double) white_pixels / (img.rows * img.cols);

    return zhanbi;
}

// 定位棋盘位置
Mat dingweiqizi_weizhi(const Mat& img) {
    Mat image = img.clone();
    Mat hsv, mask, erodeim, dilateim, gray, dst;

    cvtColor(img, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(10, 0, 0), Scalar(40, 255, 255), mask);

    erode(mask, erodeim, Mat(), Point(-1, -1), 2);  // 腐蚀
    dilate(erodeim, dilateim, Mat(), Point(-1, -1), 2);

    bitwise_and(img, img, image, dilateim);
    cvtColor(image, gray, COLOR_BGR2GRAY);

    threshold(gray, dst, 100, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(dst, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    int max_area_idx = 0;
    double max_area = 0;

    for (size_t i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > max_area) {
            max_area = contourArea(contours[i]);
            max_area_idx = i;
        }
    }

    vector<Point> approx;
    approxPolyDP(contours[max_area_idx], approx, 0.02 * arcLength(contours[max_area_idx], true), true);

    Rect bounding_box = boundingRect(approx);
    Mat checkerboard = image(bounding_box);

    return checkerboard;
}

// 定位棋子颜色及位置
vector<vector<int>> dingweiqizi_yanse_weizhi(const Mat& img) {
    Mat resized_img;
    resize(img, resized_img, Size(724, 724));

    int small_length = 38;  // 每个小格宽高
    int qizi_zhijing = 38;  // 棋子直径

    vector<vector<int>> list(19, vector<int>(19, 2));

    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            int Tp_x = small_length * i;
            int Tp_y = small_length * j;
            int Tp_width = qizi_zhijing;
            int Tp_height = qizi_zhijing;

            Mat img_temp = resized_img(Rect(Tp_x, Tp_y, Tp_width, Tp_height));
            double heise_zhanbi = Heise_zhanbi(img_temp);
            if (heise_zhanbi > 0.5) {
                list[j][i] = 0; // 黑色
                cout << "row " << j + 1 << " col " << i + 1 << " piece black" << endl;
            } else {
                double baise_zhanbi = Baise_zhanbi(img_temp);
                if (baise_zhanbi > 0.05) {
                    list[j][i] = 1; // 白色
                    cout << "row " << j + 1 << " col " << i + 1 << " piece white" << endl;
                } else {
                    list[j][i] = 2; // 无棋子
                }
            }
        }
    }

    return list;
}


void ImageRecognition::recogniton2(QImage image, std::vector<std::vector<Piece> > &boarder) {
    // 定位棋盘位置
    Mat img = QImageToMat(image);  // 转换为cv::Mat
    //Mat img = imread("C:\\Users\\weiqi\\Desktop\\f.png");
    Mat img_after = dingweiqizi_weizhi(img);
    // 定位棋盘棋子颜色及位置
    vector<vector<int>> list = dingweiqizi_yanse_weizhi(img_after);
    cout << "Final Board:" << endl;
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            cout << list[i][j] << " ";
            boarder[i][j].color = list[i][j];
        }
        cout << endl;
    }
}

int ImageRecognition::recogniton3(QImage image, std::vector<std::vector<Piece> > &boarder) {
    // 读取图像
    Mat img = imread("C:\\Users\\weiqi\\Desktop\\q.png");
    if (img.empty()) {
        cout << "无法打开图像!" << endl;
        return -1;
    }

    // 将图像转为灰度图
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // 二值化
    Mat binary;
    threshold(gray, binary, 127, 255, THRESH_BINARY_INV);

    // 进行一些形态学操作去除噪声
    Mat morph;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(binary, morph, MORPH_CLOSE, kernel);

    // 查找棋盘边缘
    vector<vector<Point>> contours;
    findContours(morph, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 选择最大轮廓，假设是棋盘的轮廓
    if (contours.empty()) {
        cout << "未找到棋盘!" << endl;
        return -1;
    }

    // 计算轮廓的矩形边界
    Rect boardRect = boundingRect(contours[0]);
    Mat board = img(boardRect);

    // 透视变换，确保棋盘是矩形
    vector<Point2f> srcPoints = {Point2f(0, 0), Point2f(board.cols - 1, 0), Point2f(board.cols - 1, board.rows - 1), Point2f(0, board.rows - 1)};
    vector<Point2f> dstPoints = {Point2f(0, 0), Point2f(BOARDWIDTH - 1, 0), Point2f(BOARDWIDTH - 1, BOARDWIDTH - 1), Point2f(0, BOARDWIDTH - 1)};
    Mat transformMatrix = getPerspectiveTransform(srcPoints, dstPoints);
    Mat rectifiedBoard;
    warpPerspective(board, rectifiedBoard, transformMatrix, Size(BOARDWIDTH, BOARDWIDTH));

    // 识别棋盘上的棋子
    vector<vector<int>> boardState(BOARDWIDTH, vector<int>(BOARDWIDTH, 2));  // 0: 空，1: 黑子，2: 白子

    // 遍历每个交点，检查是否有棋子
    for (int i = 0; i < BOARDWIDTH; ++i) {
        for (int j = 0; j < BOARDWIDTH; ++j) {
            // 计算每个格子的中心点
            Point center(i * rectifiedBoard.cols / BOARDWIDTH, j * rectifiedBoard.rows / BOARDWIDTH);
            Vec3b color = rectifiedBoard.at<Vec3b>(center);

            // 假设黑子为黑色，白子为白色，其他为无子
            if (color[0] < 100 && color[1] < 100 && color[2] < 100) {  // 黑子
                boardState[i][j] = 0;
            } else if (color[0] > 200 && color[1] > 200 && color[2] > 200) {  // 白子
                boardState[i][j] = 1;
            } else {
                boardState[i][j] = 2;  // 空
            }
        }
    }

    // 输出棋盘状态
    for (int i = 0; i < BOARDWIDTH; ++i) {
        for (int j = 0; j < BOARDWIDTH; ++j) {
            cout << boardState[i][j] << " ";
            boarder[i][j].color = boardState[i][j];
        }
        cout << endl;
    }
    return 1;
}


int ImageRecognition::recogniton4(QImage image, std::vector<std::vector<Piece> > &boarder) {
    return 0;
}




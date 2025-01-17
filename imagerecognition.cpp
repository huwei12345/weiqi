#include "imagerecognition.h"
//#include <opencv2/opencv.hpp>
//#include <iostream>

//using namespace std;
//using namespace cv;

imageRecognition::imageRecognition()
{

}

void imageRecognition::recogniton(QImage image, std::vector<std::vector<Piece> > boarder)
{
    // 读取棋盘
//    Mat img = imread("C:/Users/chenr/Desktop/board_process/go1.jpeg");

//    // 转换为灰度图像
//    Mat gray;
//    cvtColor(img, gray, cv::COLOR_BGR2GRAY);

//    // 高斯模糊
//    GaussianBlur(gray, gray, cv::Size(5, 5), 0);

//    // 边缘检测
//    Mat edges;
//    Canny(gray, edges, 50, 100, 3, false);

//    // 轮廓提取
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

//    // 找到最大的轮廓，即棋盘的轮廓
//    vector<Point> maxContour;
//    double maxArea = 0;
//    for (int i = 0;i<contours.size();i++)
//    {
//        double area = contourArea(contours[i]);
//        if (area > maxArea) {
//            maxArea = area;
//            maxContour = contours[i];
//        }
//    }

//    // 找到棋盘的四个角点
//    RotatedRect rect = minAreaRect(maxContour);

//    // 找到棋盘上的棋子
//    vector<Vec3f> circles;
//    HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, 20, 100, 19, 10, 20);

//    // 计算棋盘的大小
//    int width = static_cast<int>(rect.size.width);
//    int height = static_cast<int>(rect.size.height);
//    cout << width << " " << height<<endl;
//    // 计算每个圆形所在的格子位置（这块需要根据实际摄像头传回的数据进行修正）
//    vector<vector<int> > centers; // 存储圆心坐标和格子位置
//    int r;
//    for (const auto& center : circles) {
//        int cx = center[0];
//        int cy = center[1];
//        r = center[2];
//        // 计算格子行号和列号，从0开始
//        int row = static_cast<int>(cy / (width / 18));
//        int col = static_cast<int>(cx / (height / 18));
//        // 添加到vector中
//        std::vector<int> v1 = { cx,cy,row,col };
//        centers.push_back(v1);
//    }

//    // 颜色空间转换，将图像转换为HSV空间
//    Mat hsv;
//    cvtColor(img, hsv, cv::COLOR_BGR2HSV);

//    // 阈值分割，根据黑子和白子的颜色范围分别设置阈值，得到两个二值图像
//    Mat mask_black, mask_white;
//    inRange(hsv, cv::Scalar(0, 0, 10), cv::Scalar(180, 255, 90), mask_black);
//    inRange(hsv, cv::Scalar(0, 0, 100), cv::Scalar(180, 30, 255), mask_white);

//    // 与运算，将二值图像和原图像相与，得到黑子和白子的图像
//    Mat res_black, res_white;
//    bitwise_and(img, img, res_black, mask_black);
//    bitwise_and(img, img, res_white, mask_white);
//    cvtColor(res_black, res_black, cv::COLOR_BGR2GRAY);
//    cvtColor(res_white, res_white, cv::COLOR_BGR2GRAY);

//    // 统计每个圆形区域内的非零像素个数，判断是否有棋子，以及棋子的颜色
//    vector<pair<string, Point>> stones; // 存储棋子的颜色和位置
//    for (const auto& center : centers) {
//        int cx = center[0];
//        int cy = center[1];
//        int row = center[2];
//        int col = center[3];
//        // 在黑子图像上取一个圆形区域
//        Mat black_roi = res_black(Rect(cx - r, cy - r, 2 * r, 2 * r));
//        // 计算非零像素个数
//        int nz_count_black = countNonZero(black_roi);
//        // 如果大于阈值，则判断为黑子
//        if (nz_count_black > 50) {
//            Point p;
//            p.x = row;
//            p.y = col;
//            stones.emplace_back("black", p);
//            continue;
//        }
//        // 在白子图像上取一个圆形区域
//        Mat white_roi = res_white(Rect(cx - r, cy - r, 2 * r, 2 * r));
//        // 计算非零像素个数
//        int nz_count_white = countNonZero(white_roi);
//        // 如果大于阈值，则判断为白子
//        if (nz_count_white > 50) {
//            Point p;
//            p.x = row;
//            p.y = col;
//            stones.emplace_back("white", p);
//            continue;
//        }
//    }

//    // 输出棋子的颜色和位置信息
//    vector<vector<int>> board(19, vector<int>(19, 0));
//    for (const auto& stone : stones) {
//        string color = stone.first;
//        Point pos = stone.second;
//        int row = pos.x;
//        int col = pos.y;
//        cout << "There is a " << color << " stone at row " << row+1<< " and column " << col+1<< "." << endl;
//        board[row][col] = (color == "white") ? 1 : 2;
//    }
//    for (int i = 0; i < board.size(); i++)
//    {
//        for (int j = 0; j < board[i].size(); j++)
//        {
//            cout << board[i][j] << " ";
//        }
//        cout << endl;
//    }
}

#ifndef SGFPARSER_H
#define SGFPARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include "piece.h"
#include <QDebug>
enum class Color { Black = 0, White = 1, None = 2};


// SGF棋局树
class SGFTreeNode {
public:
    SGFTreeNode() : branchNum(0), moveNum(0) { }
    Piece move;
    std::vector<std::shared_ptr<SGFTreeNode>> branches;  // 存储不同的分支
    std::weak_ptr<SGFTreeNode> parent;
    //只针对moves
    std::vector<std::vector<Piece>> boardHistory;//size = moves.size()
    int branchNum;//第几个分支
    int moveNum;//深度 手数

    // 设置parent为shared_ptr
    void setParent(std::shared_ptr<SGFTreeNode> parentNode) {
        parent = parentNode;
    }

    // 获取父节点的shared_ptr，如果父节点已经被销毁，返回nullptr
    std::shared_ptr<SGFTreeNode> getParent() const {
        return parent.lock();  // lock()将weak_ptr转换为shared_ptr，如果父节点已销毁返回nullptr
    }
};
class SGFParser {
public:
    SGFParser() {
        head = R"(;AppName[golaxy]BlackPlayer[境由心生]BoardSize[19]Date[2025-01-0316\:27\:12]Komi[7.5]WhitePlayer[莫以成败论英])";
    }

    // 解析SGF文件
    std::shared_ptr<SGFTreeNode> parse(const std::string& filename, std::map<std::string, std::string> &setupInfo) {
        std::ifstream file(filename);
        std::string line;
        std::stringstream ss;

        // 读取整个文件内容
        while (std::getline(file, line)) {
            ss << line;
        }
        return parseSGF(ss.str(), setupInfo);
    }

private:
    std::shared_ptr<SGFTreeNode> parseSGF(const std::string& sgf, std::map<std::string, std::string> &setupInfo) {
        auto root = std::make_shared<SGFTreeNode>();
        root->boardHistory.assign(BOARDWIDTH, std::vector<Piece>(BOARDWIDTH));
        size_t pos = 0;

        parseSetupInfo(sgf, pos, root, setupInfo);
        // 处理主局面和分支
        int moveNum = 1;
        root->parent.reset();
        parseBranch(sgf, pos, root, moveNum);
        qDebug() << "get " << moveNum << " piece";
        return root;
    }

    void parseSetupInfo(const std::string& sgf, size_t& pos, std::shared_ptr<SGFTreeNode>& node, std::map<std::string, std::string> &setupInfo) {
        // 解析开局信息，直到遇到第一对括号 '(' 为止
        pos += 2;
        bool startFlag = 0;
        while (pos < sgf.size()) {
            char s = sgf[pos];
            // 解析开局的每一项（键值对）
            if (sgf[pos] == (char)';' || sgf[pos] == '(') {
                break;
            }

            // 检查是否为有效的键值对
            size_t keyStart = pos;
            size_t keyEnd = sgf.find('[', keyStart);
            if (keyEnd == std::string::npos) break;

            std::string key = sgf.substr(keyStart, keyEnd - keyStart);
            ++pos;  // Skip '['

            size_t valueEnd = sgf.find(']', keyEnd);
            if (valueEnd == std::string::npos) break;

            std::string value = sgf.substr(keyEnd + 1, valueEnd - keyEnd - 1);
            pos = valueEnd + 1;  // Skip ']'

            // 存储开局信息
            if (key == "FF") {
                setupInfo["FileFormat"] = value;
            } else if (key == "CA") {
                setupInfo["Charset"] = value;
            } else if (key == "GM") {
                setupInfo["GameType"] = value;
            } else if (key == "SZ") {
                setupInfo["BoardSize"] = value;
            } else if (key == "AP") {
                setupInfo["AppName"] = value;
            } else if (key == "PB") {
                setupInfo["BlackPlayer"] = value;
            } else if (key == "PW") {
                setupInfo["WhitePlayer"] = value;
            } else if (key == "DT") {
                setupInfo["Date"] = value;
            } else if (key == "KM") {
                setupInfo["Komi"] = value;
            }
        }
    }

    void parseBranch(const std::string& sgf, size_t& pos, std::shared_ptr<SGFTreeNode> node, int& moveNum) {
        std::shared_ptr<SGFTreeNode> cur = node;
        std::shared_ptr<SGFTreeNode> ptr = nullptr;
        while (pos < sgf.size()) {
            // 查找'('标记分支的开始
            char s = sgf[pos];
            if (sgf[pos] == '(') {
                ++pos; // Skip the '('
                // 递归解析当前分支
                int treemoveNum = 1;
                parseBranch(sgf, pos, cur, treemoveNum);
            }
            // 处理棋谱（B[]和W[]表示的黑白棋子）
            else if (sgf[pos] == 'B' || sgf[pos] == 'W') {
                char color = sgf[pos]; // 'B' -> Black, 'W' -> White
                ++pos; // Skip the color character
                if (sgf[pos] == '[') {
                    ++pos; // Skip the '['
                    size_t end_pos = sgf.find(']', pos);
                    if (end_pos != std::string::npos) {
                        std::string move = sgf.substr(pos, end_pos - pos);
                        int x = move[0] - 'a';  // 假设字母代表行列，例如a表示0行
                        int y = move[1] - 'a';  // 同理列
                        Piece piece;
                        piece.row = y;
                        piece.col = x;
                        piece.color = (int)(color == 'B' ? Color::Black : Color::White);
                        auto newNode = std::make_shared<SGFTreeNode>();
                        newNode->move = piece;
                        newNode->parent = cur;
                        if (ptr == nullptr) {
                            ptr = newNode;
                        }
                        cur->branches.push_back(newNode);
                        cur = newNode;
                        pos = end_pos + 1; // Skip the ']'
                    }
                }
            }
            // 如果遇到无关的字符跳过
            else if (sgf[pos] == ';') {
                ++pos;  // Skip the ';' for next moves or branch
            }
            // 结束条件
            else if (sgf[pos] == ')'){
                // ")"
                ++pos;
                break;
            }
        }
    }






public:
    // 将开局信息写入文件
    void writeSetupInfo(std::ofstream& file, const std::map<std::string, std::string>& setupInfo) {
        if (setupInfo.size() == 0) {
            file << head;
            return;
        }
        file << ";";
        for (auto& r : setupInfo) {
            if (r.first == std::string("Komi")) {
                file << "KM" << "[" << r.second << "]";
            } else if (r.first == std::string("FileFormat")) {
                file << "FF" << "[" << r.second << "]";
            } else if (r.first == std::string("Charset")) {
                file << "CA" << "[" << r.second << "]";
            } else if (r.first == std::string("GameType")) {
                file << "GM" << "[" << r.second << "]";
            } else if (r.first == std::string("BoardSize")) {
                file << "SZ" << "[" << r.second << "]";
            } else if (r.first == std::string("AP")) {
                file << "AP" << "[" << r.second << "]";
            } else if (r.first == std::string("BlackPlayer")) {
                file << "PB" << "[" << r.second << "]";
            } else if (r.first == std::string("WhitePlayer")) {
                file << "PW" << "[" << r.second << "]";
            } else if (r.first == std::string("Date")) {
                file << "DT" << "[" << r.second << "]";
            } else {
                file << r.first << "[" << r.second << "]";
            }
        }
    }

    // 将棋步写入文件
    void writeMove(std::ofstream& file, Piece& move) {
        if (move.color == 2) {
            return;
        }
        char color = (move.color == 0) ? 'B' : 'W';
        file << ";" << color << "[" << (char)('a' + move.col) << (char)('a' + move.row) << "]";
    }

    // 递归保存分支
    void saveBranch(std::ofstream& file, const std::shared_ptr<SGFTreeNode>& node, std::map<std::string, std::string> &setupInfo) {
        file << "(";
        {
            if (node->getParent() == nullptr) {
                writeSetupInfo(file, setupInfo);
            }
        }
        // 写入棋步
        std::shared_ptr<SGFTreeNode> cur = node;
        while (cur->branches.size() == 1) {
            writeMove(file, cur->move);
            cur = cur->branches[0];
        }
        writeMove(file, cur->move);

        // 递归保存分支，不要递归，深度大
        for (const auto& branch : cur->branches) {
            saveBranch(file, branch, setupInfo);
        }

        file << ")";
    }

    // 保存SGF文件
    bool saveSGF(const std::string& filename, const std::shared_ptr<SGFTreeNode> root, std::map<std::string, std::string> &setupInfo) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << filename << std::endl;
            return false;
        }

        // 写入文件格式、字符集、游戏类型等开局信息
        // 保存分支
        saveBranch(file, root, setupInfo);

        file.close();
        std::cout << "SGF file saved to " << filename << std::endl;
        return true;
    }

    std::string head;
};

#endif // SGFPARSER_H

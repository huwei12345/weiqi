#ifndef KATA_H
#define KATA_H

#include "piece.h"

#include <QProcess>
#include <QString>
#include "sgfparser.h"


class Kata : public QObject
{
    Q_OBJECT
public:
    Kata();
    Kata(std::vector<std::vector<Piece>> *board) : mBoard(board) {}
    int test();
    void parseShowboard(const QString &showboardOutput, std::vector<std::vector<Piece>> &board);
    std::vector<std::vector<Piece>> *mBoard;
    void reInitKata(std::shared_ptr<SGFTreeNode> head);

    Q_SLOT int startKata();
    bool isValid(Piece piece);

    Q_SLOT void getAIPiece(Piece nowPiece, int color);
    Q_SLOT void calculateScore(std::shared_ptr<SGFTreeNode> node, JudgeInfo *info);
    Q_SLOT void calculateEndScore(std::shared_ptr<SGFTreeNode> node, JudgeInfo *info);
signals:
    void getAIPieceSuccess(Piece* piece);
    void calculateScoreSuccess();
    void calculateEndResultSuccess();
private:
    std::shared_ptr<SGFTreeNode> root;
    QProcess* kataGoProcess;
    QString mKatagoOutput;
};

#endif // KATA_H

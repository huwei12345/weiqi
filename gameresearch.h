#ifndef GAMERESEARCH_H
#define GAMERESEARCH_H

#include "gamesettings.h"
#include "boardwidget.h"
#include <vector>

enum ModeType {
    PlayMode = 0,
    SearchMode = 1,
    DingShiMode = 2,
    ExerciseMode = 3,
    AIMode = 4
};

//研究模式
class GameResearch
{
public:
    GameResearch();

    std::vector<std::vector<Piece>> board;//表示棋盘状态，存储当前的棋盘布局
    std::vector<std::vector<Piece>> zeroBoard;

    //此功能由SGFTreeNode 和historyNode
    //    **MoveHistory moveHistory**：存储游戏过程中所有的历史棋步，可以用于回溯、悔棋等。

    GameSettings settings;//**：游戏设置，可能包括规则、时间等。
    TimeControl *timeControl;// = setting->timeControl**：时间控制，适用于模拟研究时的时间限制（如果有的话）。
    QColor currentPlayer;//**：当前落子的玩家。
    ModeType isInResearchMode;//**：指示是否处于研究模式。
    //    **std::vector<Move> analysisMoves**：存储玩家或AI在研究模式下进行的棋步（与历史棋局无关，纯粹用于分析）。

    //    **loadGameFromFile(const std::string& filename)**：从文件中读取棋局，恢复到研究模式。

    //    该函数负责解析SGF文件或其他棋局文件格式，将棋盘状态、历史棋步加载到当前状态。
    //    **saveGameToFile(const std::string& filename)**：将当前棋局保存到文件，便于以后查看或继续研究。

    //    show
    //    **startResearchMode()**：进入研究模式，初始化棋盘和历史棋步，准备自由落子和分析。

    //    在进入研究模式后，玩家可以任意落子，棋盘状态会即时更新。
    //    **makeMove(int x, int y)**：模拟落子并更新棋盘状态，可以是研究模式下的自由落子。

    //    该函数可以模拟任意位置的落子，进行局势分析或模拟不同的策略。
    //    **undoMove()**：悔棋功能，回到上一状态。

    //    如果玩家对某一步棋不满意，可以悔棋并尝试不同的棋步。
    //    **checkVictory()**：判断当前棋局是否已结束，或某方是否已经胜利。

    //    这个函数可以根据棋盘状态（例如，通过计算围地、提子等方式）判断是否有胜负。
    //    **analyzePosition()**：分析当前棋局，给出局势的评估。可以根据围棋规则（例如：地盘大小、提子数、禁着点等）来评估当前棋局的形式。

    //    可以是一个简单的局面分析，或者是根据某些复杂的棋局评分方法来判断局面。
    //    **simulateGame()**：模拟后续的棋步，自动进行AI对弈或者由玩家继续操作。
};

#endif // GAMERESEARCH_H

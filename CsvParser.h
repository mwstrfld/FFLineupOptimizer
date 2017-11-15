#pragma once


#include <vector>

#include <QList>

#include <Player.h>


// Forward declarations
class QStandardItem;
class QStandardItemModel;

class CsvParser
{
public:
    CsvParser();
    ~CsvParser();

    void parseRankings( Player::Position position,
                        const QString& fileName,
                        QStandardItemModel* model );

protected:
    // Helper functions
    void writeLineAndBuildVector( Player::Position position,
                                  const QStringList& line,
                                  QStandardItemModel* model );
    void addToVector( Player::Position position, const Player& player );

    // Ranking vectors
    std::vector< Player > m_overallRankings;
    std::vector< Player > m_qbRankings;
    std::vector< Player > m_wrRankings;
    std::vector< Player > m_rbRankings;
    std::vector< Player > m_teRankings;
    std::vector< Player > m_dstRankings;
    std::vector< Player > m_kRankings;
};

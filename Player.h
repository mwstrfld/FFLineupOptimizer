#pragma once


#include <QString>


class Player
{
public:
    enum Position
    {
        NONE,
        QB,
        WR,
        RB,
        TE,
        K,
        DST
    };

    Player();
    Player( const QString& name = "",
            Position position = Position::NONE,
            unsigned int overallRank = 0,
            unsigned int positionalRank = 0 );
    ~Player();

    bool nameMatch( const QString& name );

    void setName( const QString& name );
    QString getName() const;

    void setTeam( const QString& team );
    QString getTeam() const;

    void setPosition( Position position );
    Position getPosition() const;

    void setOverallRanking( unsigned int rank );
    unsigned int getOverallRanking() const;

    void setPositionalRanking( unsigned int rank );
    unsigned int getPositionalRanking() const;

protected:

    QString m_name;
    QString m_team;
    Position m_position;
    unsigned int m_overallRank;
    unsigned int m_positionRank;
};

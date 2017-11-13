#include <Player.h>


Player::Player()
{
}

Player::Player( const QString& name,
                Position position,
                unsigned int overallRank,
                unsigned int positionalRank )
    : m_name( name ),
      m_position( position ),
      m_overallRank( overallRank ),
      m_positionRank( positionalRank )
{
}

Player::~Player()
{
}


bool Player::nameMatch( const QString& name )
{
    return !QString::compare( name, m_name, Qt::CaseInsensitive );
}


void Player::setName( const QString& name )
{
    m_name = name;
}

QString Player::getName() const
{
    return m_name;
}


void Player::setTeam( const QString& team )
{
    m_team = team;
}

QString Player::getTeam() const
{
    return m_team;
}


void Player::setPosition( Position position )
{
    m_position = position;
}

Player::Position Player::getPosition() const
{
    return m_position;
}


void Player::setOverallRanking( unsigned int rank )
{
    m_overallRank = rank;
}

unsigned int Player::getOverallRanking() const
{
    return m_overallRank;
}


void Player::setPositionalRanking( unsigned int rank )
{
    m_positionRank = rank;
}

unsigned int Player::getPositionalRanking() const
{
    return m_positionRank;
}

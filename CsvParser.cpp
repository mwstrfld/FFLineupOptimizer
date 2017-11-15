#include <CsvParser.h>

#include <QDebug>
#include <QFile>
#include <QStandardItem>
#include <QStringList>


CsvParser::CsvParser()
    : m_overallRankings(),
      m_qbRankings(),
      m_wrRankings(),
      m_rbRankings(),
      m_teRankings(),
      m_kRankings(),
      m_dstRankings()
{
}

CsvParser::~CsvParser()
{
}


void CsvParser::parseRankings( Player::Position position,
                               const QString& fileName,
                               QStandardItemModel* model )
{
    if( model )
    {
        QFile file( fileName );
        if( file.open( QIODevice::ReadOnly ) )
        {
            // Read all the data into one string
            QString data = file.readAll();

            // Get rid of carriage returns
            data.remove( QRegExp( "\r" ) );

            // Local for last line
            QStringList lastStrsInLine;
            bool ready = false;

            // Read data
            QTextStream textStream( &data );
            while( !textStream.atEnd() )
            {
                auto line = textStream.readLine();
                if( !textStream.atEnd() )
                {
                    auto strsInLine = line.split( QChar( ',' ) );

                    // Check for first row of rankings
                    if( !QString::compare( strsInLine.at( 0 ), QStringLiteral( "1" ) ) && !ready )
                    {
                        // Use the last line as the headings
                        model->setHorizontalHeaderLabels( lastStrsInLine );

                        // Set ready to read the rest of the lines
                        ready = true;
                    }

                    // Write the lines and build vectors when ready
                    if( ready )
                    {
                        writeLineAndBuildVector( position, strsInLine, model );
                    }
                    else
                    {
                        // Hold onto last line
                        lastStrsInLine = strsInLine;
                    }
                }
            }
        }
    }
    else
        qDebug() << "Error reading model.";
}


void CsvParser::writeLineAndBuildVector( Player::Position position,
                                         const QStringList& line,
                                         QStandardItemModel* model )
{
    // Create the item list to add to the row
    QList< QStandardItem* > itemList;

    // Create Player instance
    Player player( "" );
    player.setPosition( position );

    // Iterate over to append to list and build vector
    for( auto i = 0; i < line.size(); ++i )
    {
        // Get the string
        auto str = line.at( i );

        // Create item and append to list
        auto item = new QStandardItem( str );
        if( i != 1 )
            item->setTextAlignment( Qt::AlignCenter );
        itemList.append( item );

        // Fill out the player
        switch( i )
        {
        case 0: // Ranking
            if( position == Player::Position::NONE )
                player.setOverallRanking( str.toUInt() );
            else
                player.setPositionalRanking( str.toUInt() );
            break;
        case 1: // Name
            player.setName( str );
            break;
        case 2: // Team
            player.setTeam( str );
            break;
        default:
            break;
        }
    }

    // Add to model to write the line
    model->appendRow( itemList );

    // Add to the positional vector
    addToVector( position, player );
}


void CsvParser::addToVector( Player::Position position, const Player& player )
{
    switch( position )
    {
    case Player::Position::NONE:
        m_overallRankings.push_back( player );
        break;
    case Player::Position::QB:
        m_qbRankings.push_back( player );
        break;
    case Player::Position::WR:
        m_wrRankings.push_back( player );
        break;
    case Player::Position::RB:
        m_rbRankings.push_back( player );
        break;
    case Player::Position::TE:
        m_teRankings.push_back( player );
        break;
    case Player::Position::K:
        m_kRankings.push_back( player );
        break;
    case Player::Position::DST:
        m_dstRankings.push_back( player );
        break;
    default:
        break;
    }
}

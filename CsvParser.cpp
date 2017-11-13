#include <CsvParser.h>

#include <QDebug>
#include <QFile>
#include <QStandardItem>


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

            // Create temp
            QString temp = "";
            QChar character = '0';

            // Read data
            QTextStream textStream( &data );
            while( !textStream.atEnd() )
            {
                textStream >> character;
                if( character == ',' )
                    checkString( temp, character, model );
                else if( character == '\n' )
                    checkString( temp, character, model );
                else if( textStream.atEnd() )
                {
                    temp.append( character );
                    checkString( temp, character, model );
                }
                else
                    temp.append( character );
            }
        }
    }
    else
        qDebug() << "Error reading model.";
}


void CsvParser::checkString( QString& temp,
                             const QChar& character,
                             QStandardItemModel* model )
{
    if( temp.count( "\"" ) % 2 == 0 )
    {
        if( temp.startsWith( QChar( '\"' ) ) &&
            temp.endsWith( QChar( '\"' ) ) )
        {
            temp.remove( QRegExp( "^\"" ) );
            temp.remove( QRegExp( "\"$" ) );
        }

        // Could possibly fail if greater than 3 repeating double quotes
        temp.replace( "\"\"", "\"" );

        auto item = new QStandardItem( temp );
        m_itemList.append( item );

        if( character != QChar( ',' ) )
        {
            model->appendRow( m_itemList );
            m_itemList.clear();
        }

        temp.clear();
    }
    else
        temp.append( character );
}

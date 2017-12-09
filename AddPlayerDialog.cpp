#include <QuestionDialog.h>
#include <ui_QuestionDialog.h>

#include <QTimer>


QuestionDialog::QuestionDialog( QWidget* parent,
                                const QString& question )
    : QDialog( parent ),
      m_ui( new Ui::QuestionDialog ),
      m_countdown()
{
    // Parent the actual UI
    m_ui->setupUi( this );

    // Set modal, can't click anything else
    setModal( true );

    // Set the question
    m_ui->questionTextBrowser->setText( question );

    // Set the default clock color to black
    m_ui->clockDisplay->setPalette( Qt::black );

    // Connect submit button signal/slot
    connect( m_ui->submitButton, SIGNAL( pressed() ), SLOT( onSubmitButtonPressed() ) );

    // Create a new QTimer and connect to update function
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( updateCountdown() ) );

    // Update every second
    timer->start( 1000 );

    // Initialize the countdown to one minute
    m_countdown = QTime::fromString( "0:30", "m:ss" );

    // Call for first time
    updateCountdown();
}


QuestionDialog::~QuestionDialog()
{
    delete m_ui;
}


void QuestionDialog::updateCountdown()
{
    // Subtract a second
    m_countdown.setHMS( 0, 0, m_countdown.addSecs( -1 ).second() );

    // Close dialog if at 0
    if( m_countdown.second() < 1 )
        close();

    // Paint numbers red, if 10 seconds or less
    if( m_countdown.second() < 11 )
        m_ui->clockDisplay->setPalette( Qt::red );

    // Get the time as text
    QString timeStr = m_countdown.toString( "m:ss" );

    // Give the illusion of a blinking time
    if( (m_countdown.second() % 2) == 0 )
        timeStr[ 1 ] = ' ';

    // Update the display
    m_ui->clockDisplay->display( timeStr );
}


void QuestionDialog::onSubmitButtonPressed()
{
    // Close this dialog
    close();
}


void QuestionDialog::done( int r )
{
    bool timedOut = m_countdown.second() < 1;

    // Let Jeopardy Board know the submitted answer
    emit answerSubmitted( m_ui->answerLineEdit->text(), timedOut );

    // Call base class
    QDialog::done( r );
}

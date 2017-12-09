#pragma once


#include <QDialog>
#include <QTime>


// Forward declarations
namespace Ui
{
    class QuestionDialog;
}


class QuestionDialog : public QDialog
{
    Q_OBJECT

public:
    QuestionDialog( QWidget* parent = 0,
                    const QString& question = "" );
    ~QuestionDialog();

signals:
    void answerSubmitted( QString, bool );

protected slots:
    void updateCountdown();
    void onSubmitButtonPressed();
    void done( int );

protected:
    // Actual UI
    Ui::QuestionDialog* m_ui;

    // Countdown time
    QTime m_countdown;
};

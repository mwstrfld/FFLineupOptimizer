#pragma once


#include <QDialog>


// Forward declarations
namespace Ui
{
    class SettingsDialog;
}


class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog( QWidget* parent = 0 );
    ~SettingsDialog();

protected slots:
    void onOkButtonPressed();
    void onCancelButtonPressed();

protected:
    // Actual UI
    Ui::SettingsDialog* m_ui;
};

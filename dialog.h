#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "dbutil.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

    void init();

    void createBaseWidget();
    void createDetailWidget();
    void createLoginWidget();

    void showDetail();
    bool registerUser(const QStringList &userInfoList);
    bool loginUser(const QString &username, const QString &password);
    void regBoxClicked(QAbstractButton *button);
    void loginBoxClicked(QAbstractButton *button);

    DbUtil db;
    QLineEdit *regUsername;
    QLineEdit *regPassword;

    QWidget *baseWidget;
    QWidget *detailWidget;
    QWidget *loginWidget;
    QVBoxLayout *mainLayout;

    QMessageBox regBox;
    QMessageBox loginBox;


};
#endif // DIALOG_H

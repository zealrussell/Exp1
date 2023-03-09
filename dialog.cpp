#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    init();

}


Dialog::~Dialog()
{

}

void Dialog::init(){
    setWindowTitle("注册");
    db.open("exp1.db");
    db.createTable("user");

    regBox.setIcon(QMessageBox::Warning);
    regBox.setWindowTitle(tr("注册成功"));
    regBox.addButton(QMessageBox::Ok);
    connect(&regBox, &QMessageBox::buttonClicked, this, &Dialog::regBoxClicked);

    loginBox.setIcon(QMessageBox::Warning);
    loginBox.setWindowTitle("警告");
    loginBox.addButton(QMessageBox::Ok);

    connect(&loginBox, &QMessageBox::buttonClicked, this, [=](){close();});

    createBaseWidget();
    createDetailWidget();
    createLoginWidget();

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(baseWidget);
    mainLayout->addWidget(detailWidget);
    mainLayout->addWidget(loginWidget);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

void Dialog::showDetail()
{
    if (detailWidget->isHidden()) {
        setWindowTitle("详情");
        detailWidget->show();
    } else {
        setWindowTitle("注册");
        detailWidget->hide();
    }
}


// 注册操作
bool Dialog::registerUser(const QStringList &userInfoList)
{

    if (db.insert("user",userInfoList)) {
        return true;
    } else {
        return false;
    }
}
// 登录操作
bool Dialog::loginUser(const QString &username, const QString &password)
{
    QString pwd = db.queryByKey("user", username);
    if (pwd.isNull() || pwd.isEmpty() || pwd.compare(password) != 0) {
        return false;
    } else {
        return true;
    }
}


void Dialog::regBoxClicked(QAbstractButton *button)
{
    qDebug() << (button == (QAbstractButton *)QMessageBox::Ok);
    baseWidget->hide();
    detailWidget->hide();
    loginWidget->show();
    setWindowTitle("登录");
}


void Dialog::createBaseWidget()
{
    baseWidget = new QWidget;
    QLabel *nameLabel = new QLabel(tr("账号："));
    regUsername = new QLineEdit;

    QLabel *pwdLabel = new QLabel(tr("密码："));
    regPassword = new QLineEdit;
    regPassword->setEchoMode(QLineEdit::Password);

    QLabel *conLabel = new QLabel(tr("确认密码："));
    QLineEdit *confirm = new QLineEdit;
    confirm->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    QPushButton *detailBtn = new QPushButton("详细信息");

    connect(detailBtn, &QPushButton::clicked, this, &Dialog::showDetail);

    // 布局
    QGridLayout *baseInfoLayout = new QGridLayout(baseWidget);
    baseInfoLayout->addWidget(nameLabel,0,0);
    baseInfoLayout->addWidget(regUsername,0,1);

    baseInfoLayout->addWidget(pwdLabel,1,0);
    baseInfoLayout->addWidget(regPassword,1,1);

    baseInfoLayout->addWidget(conLabel,2,0);
    baseInfoLayout->addWidget(confirm,2,1);

    baseInfoLayout->addWidget(detailBtn,3,0,1,2);

    baseInfoLayout->setSpacing(10);
}

void Dialog::createDetailWidget()
{
    detailWidget = new QWidget;

    QLabel *sexLabel = new QLabel(tr("性别："));
    QComboBox *sexComboBox = new QComboBox;
    sexComboBox->addItem(tr("男"));
    sexComboBox->addItem(tr("女"));

    QLabel *ageLabel = new QLabel(tr("年龄："));
    QSpinBox *ageBox = new QSpinBox;
    ageBox->setRange(0,120);
    ageBox->setDisplayIntegerBase(10);  // 10进制

    QPushButton *registerBtn = new QPushButton("注册");
    connect(registerBtn, &QPushButton::clicked, this, [=](){
        QString username = regUsername->text();
        QString password = regPassword->text();
        QString usersex = sexComboBox->currentText();
        QString userage = ageBox->text();
        QString text = QString("账号：%1  性别：%2  年龄：%3").arg(username, usersex, userage);
        QStringList list;
        list.append(username);
        list.append(password);
        list.append(usersex);
        list.append(userage);
        if (registerUser(list)) {
            regBox.setText(text);
            regBox.show();
        } else {
            QMessageBox::warning(this,"注意","注册失败",QMessageBox::Ok);
        }

    });

    // 布局
    QGridLayout *detailInfoLayout = new QGridLayout(detailWidget);
    detailInfoLayout->addWidget(sexLabel,0,0);
    detailInfoLayout->addWidget(sexComboBox,0,1);
    detailInfoLayout->addWidget(ageLabel,1,0);
    detailInfoLayout->addWidget(ageBox,1,1);
    detailInfoLayout->addWidget(registerBtn,2,0,1,2);

    detailInfoLayout->setSpacing(20);
    detailWidget->hide(); // 一开始隐藏

}

void Dialog::createLoginWidget()
{
    loginWidget = new QWidget();
    QLabel *nameLabel = new QLabel(tr("账号："));
    QLineEdit *username = new QLineEdit;

    QLabel *pwdLabel = new QLabel(tr("密码："));
    QLineEdit *password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);

    QPushButton *loginBtn = new QPushButton("登录");

    connect(loginBtn, &QPushButton::clicked, this, [=](){
        QString name = username->text();
        QString pwd = password->text();
        // 登录成功
        if (loginUser(name, pwd)) {
            qDebug() << loginBox.windowTitle();
            loginBox.setText("登录成功");
        } else {
            loginBox.setText("账号或密码不正确！");
        }
        loginBox.show();

    });

    // 布局
    QGridLayout *loginLayout = new QGridLayout(loginWidget);
    loginLayout->addWidget(nameLabel,0,0);
    loginLayout->addWidget(username,0,1);

    loginLayout->addWidget(pwdLabel,1,0);
    loginLayout->addWidget(password,1,1);

    loginLayout->addWidget(loginBtn,2,0,1,2);

    loginLayout->setSpacing(10);
    loginWidget->hide();
}








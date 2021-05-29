#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <AES-256.h>
#include <QCryptographicHash>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::HashKey(QString key)
{
    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    return hashKey;
}
QByteArray MainWindow::HashIV()
{
    QString iv="7283542938412931741265124781274912371283";
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
    return hashIV;
}
void MainWindow::on_EncryptButton_clicked()
{
    AES_Encryption encryption(AES_Encryption::ISO);

    QString key=ui->Key->text();

    QString encryptedMes=ui->encrypt->toPlainText();

    //Зашифровка и расшифровка вывод
    QByteArray encodeText = encryption.Encode(encryptedMes.toLocal8Bit(), HashKey(key), HashIV());
    QByteArray decodeText = encryption.Decode(encodeText, HashKey(key), HashIV());

    QString decodedString = QString(encryption.removePadding(decodeText));

    ui->EencrypedMess->setPlainText(encodeText);
    ui->DecryptedMess->setPlainText(decodedString);

}

void MainWindow::on_DecryptButton_clicked()
{
    AES_Encryption encryption(AES_Encryption::ISO);

    QString key=ui->Key->text();

    QString DecryptedMes=ui->Decrypt->toPlainText();
    QByteArray decodeText = encryption.Decode(DecryptedMes.toLocal8Bit(), HashKey(key), HashIV());

    QString decodedString = QString(encryption.removePadding(decodeText));

    ui->encrypt->setText(decodedString);
    ui->DecryptedMess->setText(decodedString);
}

#include "badgeswindow.h"
#include "ui_badgeswindow.h"
#include "databasemanager.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

badgeswindow::badgeswindow(const QString& username, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::badgeswindow)
    , m_username(username)
{
    ui->setupUi(this);
    setWindowTitle("Langora — Badges");
    setMinimumSize(900, 620);
    buildBadgeCards();
}

badgeswindow::~badgeswindow() {
    delete ui;
}

void badgeswindow::buildBadgeCards() {
    QList<Badge> badges = databasemanager::instance().getUserBadges(m_username);

    // Count unlocked
    int unlocked = 0;
    for (const Badge& b : badges) if (b.unlocked) unlocked++;
    ui->label_count->setText(
        QString("%1 / %2 unlocked")
            .arg(unlocked).arg(badges.size()));

    // Grid layout — 3 columns
    QGridLayout* grid = new QGridLayout(ui->scrollContents);
    grid->setContentsMargins(20, 20, 20, 20);
    grid->setSpacing(14);

    int row = 0, col = 0;
    for (const Badge& b : badges) {
        // Badge card
        QFrame* card = new QFrame();
        card->setFixedSize(264, 120);

        if (b.unlocked) {
            card->setStyleSheet(R"(
                QFrame {
                    background: #0a0f1e;
                    border: 2px solid #1d4ed8;
                    border-radius: 14px;
                }
            )");
        } else {
            card->setStyleSheet(R"(
                QFrame {
                    background: #070b14;
                    border: 1px solid #0f1629;
                    border-radius: 14px;
                }
            )");
        }

        QHBoxLayout* cardLayout = new QHBoxLayout(card);
        cardLayout->setContentsMargins(16, 0, 16, 0);
        cardLayout->setSpacing(14);

        // Icon circle
        QFrame* iconCircle = new QFrame(card);
        iconCircle->setFixedSize(52, 52);
        iconCircle->setStyleSheet(b.unlocked
                                      ? "QFrame { background: #0d1f5c; border: 2px solid #1d4ed8; border-radius: 26px; }"
                                      : "QFrame { background: #0a0f1e; border: 1px solid #0f1629; border-radius: 26px; }");

        QLabel* iconLbl = new QLabel(b.icon, iconCircle);
        iconLbl->setGeometry(0, 0, 52, 52);
        iconLbl->setAlignment(Qt::AlignCenter);
        iconLbl->setStyleSheet(QString(
                                   "color: %1; font-size: 20px; background: transparent;")
                                   .arg(b.unlocked ? "#60a5fa" : "#1e3a5f"));

        cardLayout->addWidget(iconCircle);

        // Text
        QVBoxLayout* textLayout = new QVBoxLayout();
        textLayout->setSpacing(4);

        QLabel* nameLbl = new QLabel(b.name);
        nameLbl->setStyleSheet(QString(
                                   "color: %1; font-size: 13px; font-weight: bold;"
                                   "background: transparent;")
                                   .arg(b.unlocked ? "#e2e8f0" : "#334155"));

        QLabel* descLbl = new QLabel(b.description);
        descLbl->setStyleSheet(QString(
                                   "color: %1; font-size: 11px; background: transparent;")
                                   .arg(b.unlocked ? "#334155" : "#1e3a5f"));
        descLbl->setWordWrap(true);

        QLabel* statusLbl = new QLabel(
            b.unlocked ? "✓ Unlocked" : "Locked");
        statusLbl->setStyleSheet(QString(
                                     "color: %1; font-size: 10px; font-weight: bold;"
                                     "background: transparent;")
                                     .arg(b.unlocked ? "#22c55e" : "#1e3a5f"));

        textLayout->addWidget(nameLbl);
        textLayout->addWidget(descLbl);
        textLayout->addWidget(statusLbl);
        cardLayout->addLayout(textLayout);

        grid->addWidget(card, row, col);
        col++;
        if (col >= 3) { col = 0; row++; }
    }
}

void badgeswindow::on_pushButton_back_clicked() {
    emit backRequested();
}

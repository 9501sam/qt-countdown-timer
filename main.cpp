#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QFont>

// A custom widget class for our timer window. This is good practice.
class CountdownTimer : public QWidget {
    Q_OBJECT // Macro required for any class that uses signals and slots

public:
    // Constructor
    CountdownTimer(QWidget *parent = nullptr) : QWidget(parent) {
        // --- Configuration ---
        const int TOTAL_SECONDS = 120; // 2 minutes

        // --- State Variables ---
        remainingSeconds = TOTAL_SECONDS;
        isPaused = false;

        // --- UI Widget Creation ---
        // Label to display the time
        timeLabel = new QLabel(this);
        timeLabel->setAlignment(Qt::AlignCenter);
        QFont font("Monospace");
        font.setPointSize(48);
        font.setBold(true);
        timeLabel->setFont(font);

        // Start/Pause Button
        startPauseButton = new QPushButton("Pause", this);
        startPauseButton->setMinimumHeight(40);

        // Reset Button
        resetButton = new QPushButton("Reset", this);
        resetButton->setMinimumHeight(40);

        // --- Layout ---
        // Arrange widgets vertically
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(timeLabel);
        layout->addWidget(startPauseButton);
        layout->addWidget(resetButton);
        setLayout(layout);

        // --- Core Timer Logic ---
        // QTimer will emit a 'timeout' signal every second
        timer = new QTimer(this);

        // --- Connections (Signals and Slots) ---
        // When the timer times out, call our updateDisplay function
        connect(timer, &QTimer::timeout, this, &CountdownTimer::updateDisplay);
        // When the start button is clicked, call handleStartPause
        connect(startPauseButton, &QPushButton::clicked, this, &CountdownTimer::handleStartPause);
        // When the reset button is clicked, call handleReset
        connect(resetButton, &QPushButton::clicked, this, &CountdownTimer::handleReset);

        // --- Final Window Setup ---
        setWindowTitle("Countdown Timer");
        resize(350, 250);

        // Initialize the display
        updateTimeLabel();
        timer->start(1000); // ADDED: Start the timer immediately
    }

private slots:
    // This function is a 'slot' that gets called by a 'signal'
    void updateDisplay() {
        if (remainingSeconds > 0) {
            remainingSeconds--;
            updateTimeLabel();
        } else {
            timer->stop();
            timeLabel->setText("Done!");
            startPauseButton->setText("Start");
            startPauseButton->setEnabled(false); // Disable start until reset
            isPaused = true;
        }
    }

    void handleStartPause() {
        if (isPaused) {
            // --- Start the timer ---
            if (remainingSeconds > 0) {
                timer->start(1000); // Trigger a timeout every 1000 ms (1 second)
                startPauseButton->setText("Pause");
                isPaused = false;
            }
        } else {
            // --- Pause the timer ---
            timer->stop();
            startPauseButton->setText("Resume");
            isPaused = true;
        }
    }

    void handleReset() {
        timer->stop();
        remainingSeconds = 120; // Reset to 2 minutes
        updateTimeLabel();
        startPauseButton->setText("Start");
        startPauseButton->setEnabled(true);
        isPaused = true;
    }

private:
    void updateTimeLabel() {
        // Format the remaining seconds into MM:SS format
        int minutes = remainingSeconds / 60;
        int seconds = remainingSeconds % 60;
        QString timeString = QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
        timeLabel->setText(timeString);
    }

    // --- Member Variables ---
    QLabel *timeLabel;
    QPushButton *startPauseButton;
    QPushButton *resetButton;
    QTimer *timer;

    int remainingSeconds;
    bool isPaused;
};

#include "main.moc" // Required for the Q_OBJECT macro to work correctly

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    CountdownTimer timerWindow;
    timerWindow.show();
    
    return app.exec();
}

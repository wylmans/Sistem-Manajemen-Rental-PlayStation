#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set application info
    app.setApplicationName("PlayStation Rental Management");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Your University");
    
    // Try to load stylesheet from multiple possible locations
    QStringList stylePaths = {
        "assets/style.qss",           // Relative to executable
        "../assets/style.qss",        // One level up
        "../../assets/style.qss",     // Two levels up (for build subdirs)
        QDir::currentPath() + "/assets/style.qss"
    };
    
    bool styleLoaded = false;
    QString loadedFrom;
    
    for (const QString &path : stylePaths) {
        QFile styleFile(path);
        if (styleFile.exists() && styleFile.open(QFile::ReadOnly)) {
            QString styleSheet = styleFile.readAll();
            app.setStyleSheet(styleSheet);
            styleLoaded = true;
            loadedFrom = path;
            qDebug() << "✓ Stylesheet loaded successfully from:" << path;
            qDebug() << "✓ Stylesheet size:" << styleSheet.size() << "bytes";
            break;
        }
    }
    
    if (!styleLoaded) {
        qWarning() << "⚠ Warning: Could not load stylesheet from any location:";
        for (const QString &path : stylePaths) {
            qWarning() << "  ✗" << path;
        }
        qWarning() << "Current directory:" << QDir::currentPath();
        qWarning() << "Application will run with default Qt styling.";
        
        // Apply minimal fallback styling
        app.setStyleSheet(R"(
            QMainWindow { background-color: #f5f6fa; }
            QPushButton { 
                padding: 8px 16px; 
                border-radius: 4px;
                background-color: #3498db;
                color: white;
                border: none;
            }
            QPushButton:hover { background-color: #2980b9; }
            QLineEdit { 
                padding: 6px; 
                border: 1px solid #ddd;
                border-radius: 4px;
            }
        )");
    }

    MainWindow window;
    window.resize(1200, 700);
    window.show();

    return app.exec();
}
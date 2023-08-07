#include <QApplication>
#include <QColor>
#include <QSettings>
#include <QDebug>

// Структура для хранения RGB значений цвета
struct ColorData {
    int red;
    int green;
    int blue;
};

// Пользовательский тип mColor, использующий структуру ColorData для представления цвета
class mColor {
public:
    mColor() : m_colorData{0, 0, 0} {}
    mColor(int red, int green, int blue) : m_colorData{red, green, blue} {}

    // Функция для сохранения mColor в QSettings
    void save(QSettings& settings, const QString& key) const {
        settings.setValue(key + "_red", m_colorData.red);
        settings.setValue(key + "_green", m_colorData.green);
        settings.setValue(key + "_blue", m_colorData.blue);
    }

    // Функция для загрузки mColor из QSettings
    static mColor load(const QSettings& settings, const QString& key, const QColor& defaultValue) {
        int red = settings.value(key + "_red", defaultValue.red()).toInt();
        int green = settings.value(key + "_green", defaultValue.green()).toInt();
        int blue = settings.value(key + "_blue", defaultValue.blue()).toInt();
        return mColor(red, green, blue);
    }

    // Функция для преобразования mColor в QColor
    QColor toQColor() const {
        return QColor(m_colorData.red, m_colorData.green, m_colorData.blue);
    }

private:
    ColorData m_colorData;
};
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);


    QColor originalColor(40, 63, 120);

    // Сохраняем цвет в mColor и сохраняем его в QSettings
    mColor myColor(originalColor.red(), originalColor.green(), originalColor.blue());

    QSettings qsettings(QString("test.ini"),QSettings::IniFormat);

    qsettings.beginGroup("Test");
    myColor.save(qsettings, "mColor");

    // Читаем mColor из QSettings и преобразуем обратно в QColor
    mColor loadedMyColor = mColor::load(qsettings, "mColor", QColor(100, 100, 100));
    QColor loadedColor = loadedMyColor.toQColor();

    qsettings.endGroup();


    qDebug() << "Original Color:" << originalColor.name();
    qDebug() << "Loaded Color:" << loadedColor.name();



    return 0;
}

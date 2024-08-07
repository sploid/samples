#include <QtCore>
#include <iostream>

void MessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
  if (!context.file) {
    std::cout << "no file" << std::endl;
  }
}

int main(int, char*[]) {
  const QtMessageHandler prev_handler{qInstallMessageHandler(MessageOutput)};
  qInfo() << "example";
  qInstallMessageHandler(prev_handler);
}

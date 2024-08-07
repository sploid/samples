#include <QtCore>
#include <iostream>

#define myInfo QMessageLogger(__FILE__, __LINE__, nullptr).info

void MessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
  if (!context.file) {
    std::cout << "no file" << std::endl;
  } else {
    std::cout << context.file << std::endl;
  }
}

int main(int argc, char* argv[]) {
  const QtMessageHandler prev_handler{qInstallMessageHandler(MessageOutput)};
  myInfo() << "example";
  qInstallMessageHandler(prev_handler);
}

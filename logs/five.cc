#include <QtCore>
#include <iostream>
using namespace Qt::Literals::StringLiterals;

template <typename T, size_t S>
inline constexpr size_t get_file_name_offset(const T (& str)[S], size_t i = S - 1) {
  return (str[i] == '/' || str[i] == '\\') ? i + 1 : (i > 0 ? get_file_name_offset(str, i - 1) : 0);
}

template <typename T>
inline constexpr size_t get_file_name_offset(T (& str)[1]) {
  (void)str;
  return 0;
}

namespace utility {
  template <typename T, T v>
  struct const_expr_value {
    static constexpr const T value = v;
  };
}

#define UTILITY_CONST_EXPR_VALUE(exp) ::utility::const_expr_value<decltype(exp), exp>::value

#define myInfoC(err_fingerprint) QMessageLogger(&__FILE__[UTILITY_CONST_EXPR_VALUE(get_file_name_offset(__FILE__))], __LINE__, "", err_fingerprint).info()
#define myWarningC(err_fingerprint) QMessageLogger(&__FILE__[UTILITY_CONST_EXPR_VALUE(get_file_name_offset(__FILE__))], __LINE__, "", err_fingerprint).warning()
#define myCriticalC(err_fingerprint) QMessageLogger(&__FILE__[UTILITY_CONST_EXPR_VALUE(get_file_name_offset(__FILE__))], __LINE__, "", err_fingerprint).critical()

void MessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
  QString msg_type;
  switch (type) {
  case QtMsgType::QtDebugMsg:
    msg_type = u"Debug"_s;
    break;
  case QtMsgType::QtInfoMsg:
    msg_type = u"Info"_s;
    break;
  case QtMsgType::QtWarningMsg:
    msg_type = u"Warning"_s;
    break;
  case QtMsgType::QtCriticalMsg:
    [[fallthrough]];
  case QtMsgType::QtFatalMsg:
    [[fallthrough]];
  default:
    msg_type = u"Critical"_s;
    break;
  }
  const QString file{context.file ? u"%1:%2"_s.arg(context.file).arg(context.line) : u"no file"_s};
  std::cout << msg_type.toStdString() << " " << file.toStdString() << " (" << context.category << ") " << msg.toStdString() << std::endl;
}

int main(int argc, char* argv[]) {
  const QtMessageHandler prev_handler{qInstallMessageHandler(MessageOutput)};
  qDebug() << "Message";
  myInfoC("cat_info") << "Message";
  myWarningC("cat_warning") << "Message";
  myCriticalC("cat_critical") << "Message";
  qInstallMessageHandler(prev_handler);
}

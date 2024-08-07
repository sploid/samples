#include <QtCore>
#include <iostream>

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

#define myInfo QMessageLogger(&__FILE__[UTILITY_CONST_EXPR_VALUE(get_file_name_offset(__FILE__))], __LINE__, nullptr).info

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

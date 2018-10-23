#pragma once
#include <iomanip>
#include <plog/Record.h>
#include <plog/Util.h>

namespace plog {
template <bool useUtcTime> class WollemiTxtFormatterImpl {
public:
  static util::nstring header() { return util::nstring(); }

  static util::nstring format(const Record &record) {
    tm t;
    (useUtcTime ? util::gmtime_s : util::localtime_s)(&t,
                                                      &record.getTime().time);

    util::nostringstream ss;
    ss << t.tm_year + 1900 << "-" << std::setfill(PLOG_NSTR('0'))
       << std::setw(2) << t.tm_mon + 1 << PLOG_NSTR("-")
       << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday
       << PLOG_NSTR(" ");
    ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour
       << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2)
       << t.tm_min << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0'))
       << std::setw(2) << t.tm_sec << PLOG_NSTR(".")
       << std::setfill(PLOG_NSTR('0')) << std::setw(3)
       << record.getTime().millitm << PLOG_NSTR(" ");
    ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left
       << severityToString(record.getSeverity()) << PLOG_NSTR(" ");
    ss << record.getMessage() << PLOG_NSTR("\n");

    return ss.str();
  }
};

class WollemiTxtFormatter : public WollemiTxtFormatterImpl<false> {};
class WollemiTxtFormatterUtcTime : public WollemiTxtFormatterImpl<true> {};
} // namespace plog

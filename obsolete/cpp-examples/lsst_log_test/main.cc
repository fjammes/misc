// LSST headers
#include "lsst/log/Log.h"

LOG_LOGGER getLogger() {
        static LOG_LOGGER logger = LOG_GET("testLogger");
        return logger;
}

std::string ofName = "test.log";
enum Layout_t { LAYOUT_SIMPLE, LAYOUT_PATTERN, LAYOUT_COMPONENT };

void configure(Layout_t layout) {
    std::string config = "log4j.rootLogger=DEBUG, FA\n"
        "log4j.appender.FA=FileAppender\n"
        "log4j.appender.FA.file=" + ofName + "\n";
    switch (layout) {
    case LAYOUT_SIMPLE:
        config += "log4j.appender.FA.layout=SimpleLayout\n";
        break;
    case LAYOUT_PATTERN:
        config += "log4j.appender.FA.layout=PatternLayout\n"
            "log4j.appender.FA.layout.ConversionPattern=%-5p %c %C %M (%F:%L) %l - %m - %X%n\n";
        break;
    case LAYOUT_COMPONENT:
        config += "log4j.appender.FA.layout=PatternLayout\n"
            "log4j.appender.FA.layout.ConversionPattern=%-5p %c - %m%n\n";
        break;
    }
    LOG_CONFIG_PROP(config);
}

int main() {
    unsigned char i = 101;
    configure(LAYOUT_SIMPLE);
    LOGF_DEBUG("This is DEBUG");
    LOG_INFO("This is INFO %d", i);
    LOGF_INFO("This is INFO %u" % i);
    LOG_INFO("This works");
    LOG(getLogger(), LOG_LVL_INFO, "This crash the program");
    LOGF(getLogger(), LOG_LVL_INFO, "This crash the program");
    LOG_INFO("SUCCESS");
    return 0;
}




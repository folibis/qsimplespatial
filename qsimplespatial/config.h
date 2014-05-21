#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
    static Config &instance();

    bool allowOverlappedLabels;
    bool allowLineSimplified;
private:
    Config();
};

#endif // CONFIG_H



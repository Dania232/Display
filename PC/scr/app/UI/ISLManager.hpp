#pragma once






class ISLManager
{
public:
    ~ISLManager() = default;
    virtual void Save();
    virtual void Load();
};
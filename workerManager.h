#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>

#define FILENAME "empFile.txt"

class WorkerManager
{
public:
    WorkerManager();

    void Show_Menu();

    void exitSystem();

    // 记录职工人数
    int m_EmpNum;

    // 职工数组指针
    Worker **m_empArray;

    // 添加职工
    void add_Emp();

    // 判断文件是否为空 标志
    bool m_FileIsEmpty;

    // 统计文件中的人数
    int get_EmpNum();

    // 初始化员工
    void init_Emp();

    // 显示员工
    void Show_Emp();

    // 保存到文件
    void save();

    ~WorkerManager();
};

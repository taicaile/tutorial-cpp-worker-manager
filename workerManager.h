#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

class WorkerManager
{
public:
    WorkerManager();

    void Show_Menu();

    void exitSystem();

    // 记录职工人数
    int m_EmpNum;

    // 职工数组指针
    Worker ** m_empArray;

    // 添加职工
    void add_Emp();

    ~WorkerManager();
};

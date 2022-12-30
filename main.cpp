#include <iostream>
using namespace std;
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main(int argc, char const *argv[])
{

    // Worker * worker = NULL;
    // worker = new Employee(1, "张三", 1);
    // worker->showInfo();
    // delete worker;

    // worker = new Manager(2, "李四", 2);
    // worker->showInfo();
    // delete worker;

    // worker = new Boss(3, "王五", 3);
    // worker->showInfo();
    // delete worker;

    WorkerManager wm;

    int choice = 0;

    while (true)
    {
        wm.Show_Menu();
        cout << "请输入你的选择: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 0: // 退出系统
            wm.exitSystem();
            break;
        case 1: // 增加职工
            wm.add_Emp();
            break;
        case 2: // 显示职工
            wm.Show_Emp();
            break;
        case 3: // 删除职工
            wm.Del_Emp();
            break;
        case 4: // 修改职工
            break;
        case 5: // 查找职工
            break;
        case 6: // 对职工进行排序
            break;
        case 7: // 清空文档
            break;

        default:
            system("clear");
            break;
        }
    }

    // only for windows
    // system("pause");
    /* code */
    return 0;
}

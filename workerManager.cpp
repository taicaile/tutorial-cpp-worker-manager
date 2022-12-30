#include "workerManager.h"

WorkerManager::WorkerManager()
{

    // 文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_empArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    // 文件存在，但是数据为空
    char ch;
    // 读取一个字符
    ifs >> ch;
    if (ifs.eof())
    {
        // 文件为空
        cout << "文件为空" << endl;
        this->m_EmpNum = 0;
        this->m_empArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    // 当文件存在，并且有记录的数据
    this->m_FileIsEmpty = false;
    int num = this->get_EmpNum();
    cout << "职工人数为：" << num << endl;
    this->m_EmpNum = num;

    // 开辟空间
    this->m_empArray = new Worker *[this->m_EmpNum];
    // 将文件中的数据存储到数组中
    this->init_Emp();

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        cout << "职工编号： " << this->m_empArray[i]->m_Id
             << "\t职工姓名: " << this->m_empArray[i]->m_Name
             << "\t岗位: " << this->m_empArray[i]->getDeptName() << endl;
    }
}

WorkerManager::~WorkerManager()
{
    if (this->m_empArray != NULL)
    {
        delete[] this->m_empArray;
        this->m_empArray = NULL;
    }
}

void WorkerManager::Show_Menu()
{
    cout << "**********************************" << endl;
    cout << "******* 欢迎使用职工管理系统！********" << endl;
    cout << "********* 0. 退出管理程序 **********" << endl;
    cout << "********* 1. 增加职工信息 **********" << endl;
    cout << "********* 2. 显示职工信息 **********" << endl;
    cout << "********* 3. 删除离职职工 **********" << endl;
    cout << "********* 4. 修改职工信息 **********" << endl;
    cout << "********* 5. 查找职工信息 **********" << endl;
    cout << "********* 6. 按照编号排序 **********" << endl;
    cout << "********* 7. 清空所有文档 **********" << endl;
    cout << "**********************************" << endl;
    cout << endl;
}

void WorkerManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;

    exit(0);
}

void WorkerManager::add_Emp()
{
    cout << "请输入添加职工数量：" << endl;

    int addNum = 0; // 保存用户输入数量
    cin >> addNum;

    if (addNum > 0)
    {
        int newSize = this->m_EmpNum + addNum;

        // 开辟新空间
        Worker **newSpace = new Worker *[newSize];
        // 将原来空间下数据，拷贝到新空间下
        if (this->m_empArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_empArray[i];
            }
        }

        // 批量添加新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;      // 职工编号
            string name; // 职工姓名
            int dSelect; // 部门选择

            cout << "请输入第 " << i + 1 << " 个新职工的编号： " << endl;
            cin >> id;

            cout << "请输入第 " << i + 1 << " 个新职工的姓名： " << endl;
            cin >> name;

            cout << "请输入第 " << i + 1 << " 个新职工的岗位： " << endl;
            cout << "1, 普通职工" << endl;
            cout << "2, 经理" << endl;
            cout << "3, 老板" << endl;
            cin >> dSelect;

            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        // 释放原有空间
        delete[] this->m_empArray;
        // 更改新空间的指向
        this->m_empArray = newSpace;
        // 更新职工人数
        this->m_EmpNum = newSize;
        // 保存文件
        this->save();
        // 更新文件存在标志
        this->m_FileIsEmpty = false;
        // 提示添加成功
        cout << "成功添加" << addNum << " 名新职工";
    }
    else
    {
        cout << "输入数据有误" << endl;
    }
}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_empArray[i]->m_Id << " "
            << this->m_empArray[i]->m_Name << " "
            << this->m_empArray[i]->m_DepId << endl;
    }
    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int did;

    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        num++;
    }

    return num;
}

void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int did;
    int index = 0;

    while (ifs >> id && ifs >> name && ifs >> did)
    {
        Worker *worker = NULL;
        if (did == 1)
        {
            // 普通职工
            worker = new Employee(id, name, did);
        }
        else if (did == 2)
        {
            worker = new Manager(id, name, did);
        }
        else
        {
            worker = new Boss(id, name, did);
        }
        this->m_empArray[index] = worker;
        index += 1;
    }
    ifs.close();
}

void WorkerManager::Show_Emp()
{
    // 判断文件是否存在
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            this->m_empArray[i]->showInfo();
        }
    }
}

void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入修改职工的编号" << endl;

        int id;
        cin >> id;
        int ret = this->IsExist(id);
        if (ret != -1)
        {
            delete this->m_empArray[ret];
            int newId = 0;
            string newName = "";
            int newDid = 0;

            cout << "查到：" << id << " 号职工，请输入新的职工号：" << endl;
            cin >> newId;

            cout << "请输入新姓名：" << endl;
            cin >> newName;

            cout << "请输入新的岗位" << endl;
            cout << "1, 普通员工" << endl;
            cout << "2, 经理" << endl;
            cout << "3, 老板" << endl;
            cin >> newDid;

            Worker *worker = NULL;

            switch (newDid)
            {
            case 1:
                worker = new Employee(newId, newName, newDid);
                break;

            case 2:
                worker = new Manager(newId, newName, newDid);
                break;

            case 3:
                worker = new Boss(newId, newName, newDid);
                break;

            default:
                break;
            }

            // 更新数据到数组中
            this->m_empArray[ret] = worker;

            cout << "修改成功！" << endl;
            // 保存到文件中
            this->save();
        }
        else
        {
            cout << "查找失败，查无此人！" << endl;
        }
    }
}

void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入想要删除职工编号：" << endl;
        int id = 0;
        cin >> id;

        int index = this->IsExist(id);
        if (index != -1)
        {
            // 说明职工存在
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_empArray[i] = this->m_empArray[i + 1];
            }
            this->m_EmpNum--; // 更新数组中记录人员个数
            // 同步更新到文件中
            this->save();
        }
        else
        {
            cout << "删除失败，未找到该职工" << endl;
        }
    }
}

// 判断职工是否存在
int WorkerManager::IsExist(int id)
{
    int index = -1;

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_empArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }

    return index;
}

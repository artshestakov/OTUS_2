#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
//-----------------------------------------------------------------------------
struct IPAddress
{
    IPAddress()
    {
        memset(Address, 0, 4);
    };

    unsigned char Address[4];
};
//-----------------------------------------------------------------------------
inline unsigned char StrToInt(const std::string& s);
void Sort(std::vector<IPAddress>& AddressList, int octet);
void PrintFull(std::vector<IPAddress>& AddressList); //Вывод всего списка адресов
void Print1(std::vector<IPAddress>& AddressList); //Вывод только тех адресов, где первый октет равен 1
void Print4670(std::vector<IPAddress>& AddressList); //Вывод только тех адресов, где первый октет равен 46, а второй 70
void PrintAny46(std::vector<IPAddress>& AddressList); //Вывод только тех адресов, где любой октет может быть равен 46
//-----------------------------------------------------------------------------
int main()
{
    std::vector<IPAddress> AddressList;

	std::string tmp;
	tmp.reserve(32);

    size_t pos = 0;
    size_t line_num = 0;
    size_t index = 0;

    //Читаем построчно то, что нам передали на ввод
	while (std::getline(std::cin, tmp/*, '\n'*/))
	{
        index = 0;
        ++line_num;

        //Формируем IP-адрес
        pos = tmp.find('\t');
        if (pos == std::string::npos)
        {
            std::cout << "Invalid string by line " << line_num << std::endl;
            return 1;
        }

        tmp = tmp.substr(0, pos);
        IPAddress IP;

        while ((pos = tmp.find('.')) != std::string::npos)
        {
            try
            {
                IP.Address[index++] = StrToInt(tmp.substr(0, pos));
                tmp.erase(0, pos + 1);

                if (tmp.find('.') == std::string::npos && !tmp.empty())
                {
                    //Если не нашли символ точки и строка не пустая - добавим точку в конец строки для последнего прохода
                    //Пока не придумал как сделать лучше
                    tmp += '.';
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "Can't convert octet to integer: " << e.what() << " by line " << line_num << std::endl;
                return 1;
            }
        }
        AddressList.emplace_back(IP);
    }

    //Сортируем по всем октетам
    Sort(AddressList, 0);
    Sort(AddressList, 1);
    Sort(AddressList, 2);
    Sort(AddressList, 3);

    PrintFull(AddressList);
    Print1(AddressList);
    Print4670(AddressList);
    PrintAny46(AddressList);

	return 0;
}
//-----------------------------------------------------------------------------
inline unsigned char StrToInt(const std::string& s)
{
    int i = std::stoi(s);

    if (i >= 0 && i <= 255)
    {
        return (unsigned char)i;
    }
    throw std::runtime_error(("invalid range " + s + ". Must be from 0 to 255").c_str());
}
//-----------------------------------------------------------------------------
void Sort(std::vector<IPAddress>& AddressList, int octet)
{
    bool is_need_more = false;

    for (size_t i = 0, c = AddressList.size() - 1; i < c; ++i)
    {
        IPAddress& ip_cur = AddressList[i];
        IPAddress& ip_next = AddressList[i + 1];

        if (octet == 0)
        {
            if (ip_cur.Address[octet] < ip_next.Address[octet])
            {
                std::swap(ip_cur, ip_next);
                is_need_more = true;
            }
        }
        else
        {
            if (ip_cur.Address[octet] < ip_next.Address[octet] &&
                ip_cur.Address[octet - 1] == ip_next.Address[octet - 1])
            {
                std::swap(ip_cur, ip_next);
                is_need_more = true;
            }
        }
    }

    if (is_need_more)
    {
        Sort(AddressList, octet);
    }
}
//-----------------------------------------------------------------------------
void PrintFull(std::vector<IPAddress>& AddressList)
{
    for (const IPAddress& ip : AddressList)
    {
        std::cout << (int)ip.Address[0] << '.' << (int)ip.Address[1] << '.' << (int)ip.Address[2] << '.' << (int)ip.Address[3] << std::endl;
    }
}
//-----------------------------------------------------------------------------
void Print1(std::vector<IPAddress>& AddressList)
{
    for (const IPAddress& ip : AddressList)
    {
        if (ip.Address[0] == 1)
        {
            std::cout << (int)ip.Address[0] << '.' << (int)ip.Address[1] << '.' << (int)ip.Address[2] << '.' << (int)ip.Address[3] << std::endl;
        }
    }
}
//-----------------------------------------------------------------------------
void Print4670(std::vector<IPAddress>& AddressList)
{
    for (const IPAddress& ip : AddressList)
    {
        if (ip.Address[0] == 46 && ip.Address[1] == 70)
        {
            std::cout << (int)ip.Address[0] << '.' << (int)ip.Address[1] << '.' << (int)ip.Address[2] << '.' << (int)ip.Address[3] << std::endl;
        }
    }
}
//-----------------------------------------------------------------------------
void PrintAny46(std::vector<IPAddress>& AddressList)
{
    for (const IPAddress& ip : AddressList)
    {
        if (ip.Address[0] == 46 || ip.Address[1] == 46 || ip.Address[2] == 46 || ip.Address[3] == 46)
        {
            std::cout << (int)ip.Address[0] << '.' << (int)ip.Address[1] << '.' << (int)ip.Address[2] << '.' << (int)ip.Address[3] << std::endl;
        }
    }
}
//-----------------------------------------------------------------------------


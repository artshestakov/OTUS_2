#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
void PrintFull(std::vector<IPAddress>& AddressList); //Вывод всего списка адресов
void Print1(std::vector<IPAddress>& AddressList); //Вывод только тех адресов, где первый октет равен 1
void Print4670(std::vector<IPAddress>& AddressList); //Вывод только тех адресов, где первый октет равен 46, а второй 70
void PrintAny46(std::vector<IPAddress>& AddressList); //Вывод только тех адресов, где любой октет может быть равен 46
//-----------------------------------------------------------------------------
bool ip_cmp(const IPAddress& lhs, const IPAddress& rhs)
{
    if (lhs.Address[0] != rhs.Address[0])
    {
        return lhs.Address[0] > rhs.Address[0];
    }

    if (lhs.Address[1] != rhs.Address[1])
    {
        return lhs.Address[1] > rhs.Address[1];
    }

    if (lhs.Address[2] != rhs.Address[2])
    {
        return lhs.Address[2] > rhs.Address[2];
    }

    return lhs.Address[3] > rhs.Address[3];
}
//-----------------------------------------------------------------------------
int main()
{
    std::vector<IPAddress> AddressList;

	std::string tmp;
	tmp.reserve(48);

    size_t pos = 0;
    size_t line_num = 0;
    size_t index = 0;

    //Читаем построчно то, что нам передали на ввод
	while (std::getline(std::cin, tmp))
	{
        index = 0;
        ++line_num;

        //Формируем IP-адрес
        pos = tmp.find('\t');
        if (pos == std::string::npos)
        {
            std::cout << "Invalid string by line " << line_num << std::endl;
            return EXIT_FAILURE;
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
                return EXIT_FAILURE;
            }
        }
        AddressList.emplace_back(IP);
    }

    std::sort(AddressList.begin(), AddressList.end(), &ip_cmp);

    //Выводим адреса в соответствии с заданием
    PrintFull(AddressList);
    Print1(AddressList);
    Print4670(AddressList);
    PrintAny46(AddressList);

    return EXIT_SUCCESS;
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


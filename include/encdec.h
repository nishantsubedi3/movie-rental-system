void encrypt(std::string *str)
{
    for (int i = 0; i < str->length(); i++)
    {
        (*str)[i] = (*str)[i] + 12;
    }
}

void decrypt(std::string *str)
{
    for (int i = 0; i < str->length(); i++)
    {
        (*str)[i] = (*str)[i] - 12;
    }
}
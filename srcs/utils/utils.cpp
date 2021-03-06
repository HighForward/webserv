//
// Created by Timothe Lecouvreur on 12/01/2021.
//

#include <stdlib.h>
#include <iostream>
#include <vector>

namespace Utils {
	std::vector<std::string> explode(const std::string& s, const std::string& charset)
	{
		std::string buff = "";
		std::vector<std::string> v;

		for(size_t i = 0; i < s.size(); i++)
		{
			char n = s.at(i);
			if(charset.find(n) == std::string::npos)
				buff+=n;
			else
			if(charset.find(n) != std::string::npos && buff != "") {
				v.push_back(buff);
				buff = "";
			}
		}
		if(buff != "")
			v.push_back(buff);

		return v;
	}

	std::string removeWhitespaces(const std::string &string)
	{
		std::string withoutWhitespaces = string;
		std::string::iterator it = withoutWhitespaces.begin();
		while (it != withoutWhitespaces.end()) {
			if (*it == ' ' || *it == '\t' || *it == '\r')
				it = withoutWhitespaces.erase(it);
			else
				it ++;
		}
		return (withoutWhitespaces);
	}

	std::string decodeBase64(const std::string &token)
	{
		std::string out;

		std::vector<int> T(256,-1);
		for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

		int val=0, valb=-8;
		std::string::const_iterator it = token.begin();
		while (it != token.end()) {
			unsigned char c = *it;
			if (T[c] == -1) break;
			val = (val << 6) + T[c];
			valb += 6;
			if (valb >= 0) {
				out.push_back(char((val>>valb)&0xFF));
				valb -= 8;
			}
			it++;
		}
		return out;
	}

	/**
	 * Génère un token aléatoire de la taille voulue
	 * @param len la taille du token généré
	 * @return le token généré
	 */
	std::string generateToken(unsigned int len)
	{
		std::string token, charset = "abcdefghijklmnopqrstuvwxyz0123456789";
		while (len -- > 0) {
			token += charset[rand() % charset.size()];
		}
		return token;
	}

	std::string toUppercase(std::string string)
	{
		std::string uppercase = string;
		for (std::string::iterator it = uppercase.begin(); it != uppercase.end(); it++)
			*it = std::toupper(*it);
		return (uppercase);
	}

	std::string replaceAll(std::string string, char haystack, char needle)
	{
		std::string replaced = string;
		for (std::string::iterator it = replaced.begin(); it != replaced.end(); it++) {
			if (*it == haystack)
				*it = needle;
		}
		return (replaced);
	}

	void replaceString (std::string &fileContent, const std::string &replace, const std::string &newString)
	{
		size_t pos = 0;

		while ((pos = fileContent.find(replace)) != std::string::npos)
		{
			fileContent.replace(pos, replace.length(), newString);
			pos += newString.length();
		}
	}

	int	ft_strlen(const char *str)
	{
		int	i;

		i = 0;
		if (!str)
			return (0);
		while (str[i] != '\0')
			i++;
		return (i);
	}

	char		*ft_strdup(const char *str)
	{
		int		i;
		char	*res;

		i = 0;
		if (!(res = (char*)malloc(sizeof(char) * (Utils::ft_strlen(str) + 1))))
			return (NULL);
		while (str[i] != '\0')
		{
			res[i] = str[i];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
}
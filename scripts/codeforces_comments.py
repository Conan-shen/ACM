# 导入库
import urllib.request
import bs4
from bs4 import BeautifulSoup
import sys
import os
import time


def divTextProcess(div):
    """
    处理<div>标签中<p>的文本内容
    """
    strBuffer = ''
    # 遍历处理每个<p>标签
    for each in div.find_all("p"):
        for content in each.contents:
            # 如果不是第一个，加换行符
            if (strBuffer != ''):
                strBuffer += '\n\n'
            # 处理
            if (type(content) != bs4.element.Tag):
                # 如果是文本，添加至字符串buffer中
                strBuffer += content.replace("       ",
                                             " ").replace("$$$", "$")
            else:
                # 如果是html元素，如span等，加上粗体
                strBuffer += "**" + \
                    content.contents[0].replace(
                        "       ", " ").replace("$$$", "$") + "**"
    # 返回结果
    return strBuffer


def find_ID(url):
    tmps = url.split('/')
    res = []
    idx = 0
    for str in tmps:
        if len(str) == 1:
            res.append(str)
        else:
            try:
                val = int(str)
                res.append(str)
                idx = len(res) - 1
            except:
                continue
    return res[idx ^ 1] + res[idx]


def work(url):
    # 获取网页内容
    html = urllib.request.urlopen(url).read()
    # 格式化
    soup = BeautifulSoup(html, 'lxml')
    # print(soup)
    # 存储
    data_dict = {}
    # 找到主体内容
    mainContent = soup.find_all(
        name="div", attrs={"class": "problem-statement"})[0]
    # Limit
    # 找到题目标题、时间、和内存限制
    # ID
    data_dict['ID'] = find_ID(url)
    try:
        # Title
        data_dict['Title'] = mainContent.find_all(
            name="div", attrs={"class": "title"})[0].contents[-1]
    except:
        pass
    try:
        # Time Limit
        data_dict['Time Limit'] = mainContent.find_all(
            name="div", attrs={"class": "time-limit"})[0].contents[-1]
    except:
        pass
    try:
        # Memory Limit
        data_dict['Memory Limit'] = mainContent.find_all(
            name="div", attrs={"class": "memory-limit"})[0].contents[-1]
    except:
        pass
    try:
        # tag
        tags = soup.find_all(name='span', attrs={"class": "tag-box"})
        real_tags = []
        for tag in tags:
            print(tag.contents)
            real_tags.append(tag.contents[-1].replace('\r\n', '').strip())
        data_dict['Problem_tags'] = ", ".join(real_tags)
        print(data_dict['Problem_tags'])
    except:
        pass

    try:
        # 处理题目描述
        data_dict['Problem Description'] = divTextProcess(
            mainContent.find_all("div")[10])
    except:
        pass

    try:
        div = mainContent.find_all(
            name="div", attrs={"class": "input-specification"})[0]
        data_dict['Input'] = divTextProcess(div)
    except:
        pass

    try:
        div = mainContent.find_all(
            name="div", attrs={"class": "output-specification"})[0]
        data_dict['Output'] = divTextProcess(div)
    except:
        pass

    try:
        # Input
        div = mainContent.find_all(name="div", attrs={"class": "input"})[0]
        data_dict['Sample Input'] = div.find_all("pre")[0].contents[0]
    except:
        pass
    try:
        # Onput
        div = mainContent.find_all(name="div", attrs={"class": "output"})[0]
        data_dict['Sample Output'] = div.find_all("pre")[0].contents[0]
    except:
        pass

    try:
        div = mainContent.find_all(name="div", attrs={"class": "note"})[0]
        data_dict['Note'] = divTextProcess(div)
    except:
        pass

    data_dict['Source'] = '[' + data_dict['Title'] + ']' + '(' + url + ')'

    return data_dict


def create_description(data_dict):
    res = []
    for each in data_dict.keys():
        res.append('### ' + each + '\n')
        res.append(data_dict[each].replace(
            "\n\n**", "**").replace("**\n\n", "**") + '\n\n')
    return "".join(res)


def build_file_name(name):
    names = name.split('.', 1)
    name = names[1]
    print(name)
    names = name.split(' ')
    res = []
    for tmp_name in names:
        if len(tmp_name) >= 2:
            res.append(tmp_name[0].upper() + tmp_name[1:])
        elif len(tmp_name) == 1:
            res.append(tmp_name[0].upper())
    return "".join(res)


def create_cpp_desc(data_dict):
    author = sys.argv[2]
    date = time.strftime("%Y-%m-%d", time.localtime())
    res = []
    res.append("// Source : " + data_dict['Source'] + '\n')
    res.append("// Author : " + author + '\n')
    res.append("// Date   : " + date + '\n')
    return "".join(res)


def main():
    url = sys.argv[1]
    # print (find_ID(url))
    data_dict = work(url)
    file_name = build_file_name(data_dict['Title'])
    pwd = os.getcwd()
    file_loc = pwd + '\\..\\codeforces\\' + file_name
    if not os.path.exists(file_loc):
        os.makedirs(file_loc)
    descript_loc = file_loc + '\\description'
    with open(descript_loc, mode='w', encoding='utf-8') as fd:
        fd.write(create_description(data_dict))
    cpp_loc = file_loc + '\\' + file_name + '.cpp'
    if not os.path.isfile(cpp_loc):
        with open(cpp_loc, mode='w', encoding='utf-8') as fd:
            fd.write(create_cpp_desc(data_dict))


if __name__ == "__main__":
    main()

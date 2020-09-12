from codeforces_comments import work, build_file_name
import sys
import os
curPath = os.path.abspath(os.path.dirname(__file__))
sys.path.append(curPath)


def main():
    url = sys.argv[1]
    data_dict = work(url)
    pwd = os.getcwd()
    readme_loc = pwd + '\\..\\README.md'
    file_name = build_file_name(data_dict['Title'])
    cpp_loc = './codeforces/' + file_name + '/' + file_name + '.cpp'
    with open(readme_loc, mode='a', encoding='utf-8') as fd:
        res = '|' + data_dict['ID'] + '|' + data_dict['Source'] + '|' \
            + '[C++](' + cpp_loc + ')' + '|' + \
            data_dict['Problem_tags'] + '|\n'
        fd.write(res)


if __name__ == "__main__":
    main()

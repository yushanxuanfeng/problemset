import requests
import os
import tqdm
import shutil
import zipfile
import subprocess

headers = {
    b"Accept": b"text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
    b"Accept-Encoding": b"gzip, deflate, br",
    b"Accept-Language": b"zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6",
    b"Cache-Control": b"max-age=0",
    b"Cookie": b"_uid=762646; SpilopeliaState=c0d9ace5c4df14076569f35a\
        38a2db3e629b6efd;__client_id=072fdc6cd6e5838a65745922ff8b7be6f5d88d14",
    b"Dnt": b"1",
    b"Sec-Ch-Ua": b'"Not_A Brand";v="8", "Chromium";v="120",\
        "Microsoft Edge";v="120"',
    b"Sec-Ch-Ua-Mobile": b"?0",
    b"Sec-Ch-Ua-Platform": b'"Windows"',
    b"Sec-Fetch-Dest": b"document",
    b"Sec-Fetch-Mode": b"navigate",
    b"Sec-Fetch-Site": b"none",
    b"Sec-Fetch-User": b"?1",
    b"Upgrade-Insecure-Requests": b"1",
    b"User-Agent": b"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 Edg/120.0.0.0",
}


def mkdir(path):
    if not os.path.exists(path):
        os.mkdir(path)


def safe_open(path, mode="w"):
    return open(path, mode, encoding="utf8")


def get_problem_description(url, fp1, fp2):
    resp = requests.get(url, headers=headers).json()["currentData"]["problem"]
    data = f"""## 问题描述
{resp['description']}

## 输入格式
{resp['inputFormat']}

## 输出格式
{resp['outputFormat']}

## 样例输入
{resp['samples'][0][0]}

## 样例输出
{resp['samples'][0][1]}

## 评测数据规模
{resp['hint']}"""

    data = data.replace(r"\%", "$%$").replace("$%$$", "$%")
    fp1.write(data)

    data = f"""时间限制：{resp['limits']['time'][-1] * 1.25 / 1000}s
空间限制：{resp['limits']['memory'][-1] * 1.25 / 1024}MB
知识点："""
    fp2.write(data)


def get_problem_solution(url, fp):
    resp = requests.get(url, headers=headers).json()["currentData"]["solutions"][
        "result"
    ]
    fp.write(resp[0]["content"])


def make_problem(code):
    mkdir(f"./{code}")
    prefix = "https://www.luogu.com.cn/problem/"
    suffix = "?_contentOnly=1"
    get_problem_description(
        f"{prefix}/{code}{suffix}",
        safe_open(f"./{code}/题面.md"),
        safe_open(f"./{code}/题目说明.txt"),
    )
    get_problem_solution(
        f"{prefix}/solution/{code}{suffix}", safe_open(f"./{code}/题解.md")
    )
    safe_open(f"./{code}/std.cpp").close()
    mkdir(f"./{code}/data")


def generate(
    name,
    cpp_version="c++17",
    numbers=range(1, 11),
    samples=range(1, 6),
):
    def compile_to(src, dst):
        options = '-O2 -Wall -g "-Wl,--stack=998244353" -I ./generator'
        os.system(f"g++ --std={cpp_version} {src} -o {dst} {options}")

    print("Compiling source code...", end="")
    generate_path = f"./{name}/gen.cpp"
    std_path = f"./{name}/std.cpp"
    data_path = f"./{name}/data"
    samples_path = f"./{name}/samples"
    compile_to(generate_path, "runner.exe")
    compile_to(std_path, "std.exe")
    mkdir(data_path)
    mkdir(samples_path)
    print("-Done.")
    for i in tqdm.tqdm(numbers, desc="Data making..."):
        subprocess.run(
            f"runner.exe data_hash_seed_{i} -t {i} -mode 0",
            stdout=safe_open(f"{data_path}/{i}.in"),
        )
        subprocess.run(
            "std.exe",
            stdout=safe_open(f"{data_path}/{i}.ans"),
            stdin=safe_open(f"{data_path}/{i}.in", "r"),
        )

    for i in tqdm.tqdm(samples, desc="Samples making..."):
        subprocess.run(
            f"runner.exe sample_hash_seed_{i} -t {i} -mode 1",
            stdout=safe_open(f"{samples_path}/{i}.in"),
        )
        subprocess.run(
            "std.exe",
            stdout=safe_open(f"{samples_path}/{i}.ans"),
            stdin=safe_open(f"{samples_path}/{i}.in", "r"),
        )

    os.unlink("./runner.exe")
    os.unlink("./std.exe")
    print("-Done.")
    zip = zipfile.ZipFile(f"./{name}.zip", "w", zipfile.ZIP_DEFLATED)
    zip.write(f"./{name}/problem.md")
    zip.write(f"./{name}/std.cpp")
    for num in range(1, 11):
        zip.write(f"./{name}/data/{num}.in")
        zip.write(f"./{name}/data/{num}.ans")
    zip.close()


def create_template(name):
    mkdir(f"./{name}")
    shutil.copy("./example.md", f"./{name}/problem.md")
    safe_open(f"./{name}/problem.txt").write(
        """时间限制：1s
空间限制：512MB
知识点："""
    )
    safe_open(f"./{name}/std.cpp").write(
        """#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    return 0;
}"""
    )
    safe_open(f"./{name}/gen.cpp")
    mkdir(f"./{name}/data")

def generate_template(name):
    mkdir("./"+name)
    shutil.copy("./example.md", f"./{name}/problem.md")
    with open(f"./{name}/solution.md", "w"):
        pass
    with open(f"./{name}/std.cpp", "w"):
        pass

generate_template("Counting on a Tree")

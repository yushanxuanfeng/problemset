
from requests import get
from tqdm import tqdm

src = """https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTG2eFDvPYlicUqenWFCeWWwLpI0jBNHicVwx4Icq1unR8WlaiavDtNgE9w/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGT3vN1Ge4bapFicibK7xzyicPQrWKHtSkphyJPVhficdibHK1Hb3IXicJNUguw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTRYCbVlX3Wfb8ia2UKG8fKG0fFQl29ClAKXvo29qOMicTFNQhUL4qaowQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTlYycSjOq6yDE6jk3NMsKhXoe8bbyxGtNyWdWArWfCAgnYW7YKhPb8Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTK33T4UvOeE06QKYxISs9drrZ3ic6R2txPZmmYjZqia8Q9Gg4FPJHV9DQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTWibFlqqFTXRwd8vveVkdwv3TPRMGgMFOgrsuOMNbUCRX90n3L0GbsKw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTx3SpH4ibquuuDRZITbiaIanouuYxZsea1xiaBD0wv8TzI0xJXagtrFghQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTHm1tKpTct6NbGxBJpOzfiamsox1yfPb3QmhnbA0UUZwxtAkehJvoAqw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTuPZ2jQicmgfupnW6ZmgTNdrrDhOXnZdpWnYedtcTvDKIbKVarzA1xBw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTyEtSrjYPgaL2tqfs2WxjwvrkicDmQMvby21neNVpjbK0YArczMxS65Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTygNRGs4fdeq3icicusdxOicTcPETuTtQGfqGSicfY7mGpgoU1A9qibk6E4Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTUJKFxOyDibx0GcryrnOcw4mtzks1K4ib2cOmCibEFGZdSdpKFC7zv6ITA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGT7CETZ6OoKNIt3e0SqFb4c2oVYrmsK6zFt664Xc89aevlViaTwxzlI3g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTCk3wOoIXjIh2HW1Blo8Z4RamWZKI3QQInsicyQVeN1ABKhNx3oaYMRA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTroicG9vibvotucTibkZWibG2YKQoUySYfyd8psFQrv6ovCjIb9bZ05xaqQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTLZuLa0bxJpbWVTNouvJZP2kGnBQWGmjhtoibUGCcfgExK2l3E0wY8Qg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTibMZHnjmNwMrbws0s0E4okazibdHTdxJz6MgI1r2mtabokpXJGicl1hyw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTDA8HNBILcatRVNEnJrANV6ZRZ9E32xLoqS6BVxY7Y8Lv5Me2hzNuVA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTMMiaAibN66Rv2AYdtE4xSnTHpUzqdWxb0VjtKDIKchsjjqRdXIWygA0g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTz15PZ5dRn3T3Mia5CSwmtcJh2UGYcGfj8fTdVzXSYibiaHWtZDicnpxLHw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTLlBWGx4Miaf40NTzCR3h62PEduaDAXJnK2KJVCD4kPkSG5UgQiaVoHOw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTBvyOhymgCtricXG4dOicYl2iaYUAjbibU5EdwoJficWBxJIzwyUwVHxoLxA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTia9kC471uDrH7JUkh804ZwJEZVJ3FiclYcfLmyUkKytSej9V84ia8hnmQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTnGmkKp3IjeJXWxLREkLoy7J5w7bibnZS4DiaEwXuhHPCyWX6JiakBz00Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTZYugd01NxiaabkOgdzBHInktcfespe1rsRYBM7hgdwgzbkMHeOpvCtw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGT5uVhFhjeZm4mGby450AIicHrlSfamjYt73KFRa9jBTE71adYe5JUYuQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTMhLgW71IjaOa1fGg6mbOVCpXFQpltaae1yTH5rAT02vHowrz3bOlIg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTblANkTW2me2FFPIQTk4SLuZeEH31drozOB2iaFyFdMUIiaZfCEvJzttQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGToZJZ4ib4WpXLARv75DaQDFbXMLS1Olku4MlZ5PmDS7EHpvsKDGXeGNw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTCiaZicsDbbYVyFhul3PGiak9ibGa00hOC0FUfOCznKrfr3QbxlgAK8AibQw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTU44qPfYJ12Y304wIxvmVuodhwy2YNjXO1e12190xVDcoX8VZ2ZPmfA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1
https://mmbiz.qpic.cn/mmbiz_png/6dwkfR4c7zBwj21ODwIRIpsZljJNVYGTAGiaWSQgrggDAavUnlYnQnCaztxfnbGzZCL4gAgS0oKUMh3YqKvwQ1g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1""".splitlines()


for i in tqdm(range(len(src))):
    with open(f"./data/{i}.jpg", "wb") as f:
        f.write(get(src[i]).content)

input()

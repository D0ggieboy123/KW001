def news_at_ten(txt, n):
	temp = txt
	txt = " "*n
	txt += temp
	lst = [txt[i:i+n]for i in range(len(txt)-n+1)]
	return lst
news_at_ten("Hello World",5)
print


import asyncio
import time
async def count():
    for i in range(789457890547805790750780278350708209723480459389375823590283758934290345684576289057623890762389762398576358723645827365982375623874565823465234650923846278956045876058736450893456802375623845762380457):
        print(i)
        if i % 2 == True:
            time.sleep(0.00000000000000000000000000000000001)
        else:
            await asyncio.sleep(0.0000000000000000000000000000000001)
async def main():
    await asyncio.gather(count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count(),count())
asyncio.run(main())
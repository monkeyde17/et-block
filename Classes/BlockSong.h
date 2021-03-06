#ifndef _BLOCK_SONG_H_
#define _BLOCK_SONG_H_

#define SONGCNT 41

const static char *szSong[SONGCNT] = {
//SONG 1
"LOQSONQSSTUVTSQPOOOQPOOOPQPOMPQPLOQSONQSSTUVTSQPOOOQPOOOPQPMNOPOQSQPOSNMNMNMLQSQPOSNMNOOOPQPLOQSONQSSTUVTSQPOOOQPOOOPQPMNOPO",
//SONG 2
"QQQQPONPPPOLQPOOOLQPOOPQQQQPONPPPOLQPOOOLQPOOPPQRRRRRQPOOOPPLSSSRQPPPQQMRQRQPOONOLQRQRQPOPSLQRSRQSLQRSRQSLQRSRQOPPPQOSSOONOOSSOONOORRQQPPORRQQPPOLQRSRQSLQRSRQSLQRSRQOPPPQOSSOONOOSSOONOORRQQPPOORQPOMOO",
//SONG 3
"TVUTSTQTSTVUVUTUVVWXXXXWVUTUSTVUTSTQSTXWVUVVUTTTTSSTQSSTXWVUVVVUTTSUT",
//SONG 4
"LONOLLONOLLONOOOMMLLONOLLQPPOLONOMMMOTSPPRRQQQQNPOONOONORLSRQPPPRRQQQQVUTUVVPOTTTSSSLSRQQRQQRQRQPOOQSTTTSPPRQOQSTTTSPPRQRQPOPQMMOONO",
//SONG 5
"JKLLLLLKJIILNNONOOOPQNNLHMMMJMOLLLLJHKKKJKLMMMOMLJKJJKLLLLJIHHONMLMLJHHMMLLLKJOOOONOPPLRQLLRPLRQRQRQPOONMMQMQMLLQLQLRQRQOPLRQLLRSPLRQQQRQPQONMMQMQMLLQLQPOMOPNMNMNQPOO",
//SONG 6
"OPQQQRQPPOPPSPONOOOQQOOMNNQNMLMMMRRQSOMLMMMRROOMPOOPQQQRQPPOPPSPONOOOQQOOMNNQNMLMMRRQSOMLMMMRROOONO",
//SONG 7
"STVTXXTWWWVUVWXWSVVUTUVRRRVVWVSSSSYXWXXSTVTXXTWWWVUVWXWSVVVUTUVRRRVVWVSSSSTUVVUVV",
//SONG 8
"JJKLLKJIHHIJJIIJJKLLKJIHHIJIHHIIJHIJKJHIJKJIHIEJJKLLKJIHHIJIHH",
//SONG 9
"OOSSTTSRRQQPPOSSRRQQPSSRRQQPOOSSTTSRRQQPPO",
//SONG 10
"HHIJLMONNNLJIIIJKMOQPPNLHHIJLMONNNLJIIIJKMOQPPNLMLMLMNNMNPPPPNOPQQQPPPOQNLMLMOPQQPQQPOPOMMLMOPQQPQQSTSQQQQPPOPOMQQRQPOPQQQPPOPOMOO",
//SONG 11
"JJIJJLJIJHHIJLJIIHIJLMLMLLJLEJIJLJIIIHIJJIJJLJIJHHIJLJIIHIJLMLMLLJLJIJLJIIHHIJJLMMQPOOMLMLJIHFHIIHIHIJJLMMQPOOPOLLJNOHIJIH",
//SONG 12
"QSQPQPQQPMOQPPOMOPQSPQTSSPOPOMOPQSPQTSSQPQPOSTQMQPPOQSVSTTSQQSSQSTVWVSQPSQQQSVSTVWVSQSVTQPQSXWWV",
//SONG 13
"HKKKHLJKHKNNMLKJKLHKKKHLJKHKMOMKILMKNMLIIJKLLNMLIIJKLLHKKKHLJKHKMOMKILMKILMKK",
//SONG 14
"HIJJJJIJLJJLMMMNLJJIHHHHFJLHIIIHLJIHIJJJJIJLJJLMMMMNLJLLLMOOMKILLMOOMOPLLLQQQQQPPONOOOPJLLLMOOOOPMOOOPPPPOQPLLLLQQQSQPPONOOOPJLLLMOOOOPMOOOPPPOQPO-",
//SONG 15
"LLJIJFIJLJILLJIJEIJLIHHIJLMLJLJJIIHIHIHIIJLJJLLJIJFIJLJILLJIJEIJLIHHIJLMLJLJJIIEJIIH",
//SONG 16
"MNOOOONQQTTTSRSOORRRSQNQPPONOONOOOONQQTTTSRSOORRRQPNOM",
//SONG 17
"JKJGHJMONLJJKJGHJMONLQMMMOQLKMPPQRPQRQMPQRPQRMMQRSQRSMPQRMRSKPQPQRQJKJGHJMONLJJKJGHJMONLM",
//SONG 18
"LJLIJIHHGFGHGHIJLJLPONOHGFGHGHIHLMNONONMLMLHIJKJKLHIJLMNONONPOPOQLHIJKJKJIHGHLMNONOPONMLHIJKJKLHHMLLMNONOPOPQL,HIJKJKLHHMLLMNONOPOPQL,HIJIJILHIJHLMNONOMNLKLJJJKLJEEIIIJKIEEHHHIJIGHGFGHGFEFMLIKJIHHGFIIHFFGH",
//SONG 19
"LOPQPOQPLLJMNONMONJLMLLKKOJJPOPQRQQPOMPLOPQPOQPNLQMNONMONJLMLLKKOPQOMNOMOTSSPOSQQPONOMJMOPOTRRQRMNOPQRSSSTOSNPOPQMORQRSPPOSQQPONOMJMOPOTRRQRMNOPQRSSSTOSNPOPQRMRQOPO",
//SONG 20
"MQNMOPOQMTSTSPRQMTSPQRQOMQPNMMQNMOPOQMTSTSPRQMTSPQRQPOMPONMMNOPQONLMOPQQMNOPQONLMOPOOMPONMMNOPQONLMOPQQMNOPQONLMOPOOOOPQONLONMNT",
//SONG 21
"MLJLOMLMJLMLJIHFLJIIJLLMJIHLJIHFHE",
//SONG 22
"OPQRSSSRQRRRQPOQSOPQRSSSRQRRRQPOQOTTTSRSSSRQRRRQPOQSTTTSRSSSRQRRRQPOQO",
//SONG 23
"CEFHIFHELOMLJLIIJGFEFHICHFEFHEJLGIFHECECEFGIFEFHILJIJIHFECHFHFECEFHE",
//SONG 24
"OP-QSSSSQSVVVVTQSOOOOOPQSSSTQPPPQQOPOP-QSSSSQSVVVVTQSOOOOOPQSSSTQPPPOMLO",
//SONG 25
"QQSTTTQQSTTTSQSTQSTQQSTTTTSQPQSPQQQSTTTQQSTTTSQSVUSQTQQPOPQPOPSPQM",
//SONG 26
"ONOPOLJKKKLJONOPOLLMMMONONOPQOLJOPOLJONOPQOLORQPOQQRSTOOPQPPQRSSRQPQQRSTSSUUVUSPQRQRSQRSTOOPQPPQSQUUQVVUVTSOOTSRQRSTSQRSTOOPQPPQRSSRQPQQRSTSSUUVUSPQRQRSQRSTOOPQPPQSQUUQVVUVTSOOTSRQRS",
//SONG 27
"IJJIJLJIIJJIJMLJIHFHIIFHIFHIJIIJJIJLJIIJJEIJMLJIHFHIIFHIIHIJIHFHFHFHIHFHFHFHJHHJJJMLJJIIEIJJIJLMLHIJMLJLLMOMLJLJHIJHFJIEIJJIJLMLHIJMLJLLMOMLJLJHFJIHHFHIHH",
//SONG 28
"IHIJIIHIHFFIIHIJIIHIHFFELLLJJJKLKKIIJHHFHMMMLLIHIJHHIHHFIIHIJIIHIJLJLLLLMLJKLKKIIHJIHFIHIHLLLMNMLJJJIILLLJIIHIHIJJHHIJIJLJIHIFHHIJIJLMLLJJJIILLLMNMLJJJIILLLJIIHIHIJJHHIJIJLMLLJLMMLJLJIIHIJIHFH",
//SONG 29
"MMNNOONNMMJJHHFFLLKKJKLKKKLLMMNNLLIIKKJJIIKJJFHJIJFHJIJFHKJKFHKJKKJKKLLMLMJQMOQPQMOQPQMORQRMORQRRQRRSSTSTQOJJKKIINNIIJJHHMLMHHIIGJIJOOOPPONMLLMLJOOOPPONMLLMLM",
//SONG 30
"JMMMMMMMMJKLKJLLLLLLLMNNJJMMMMMMMMQQPNNNNNJONONJMMMMMMMMJKLKILLLLLLLMNNJJMMMMMMMMQQPNNNNNNNMNMQTQQQQOMJJQPJSSSSSSSTUUQQTQQQQOMJJQPPPPPPJNNM",
//SONG 31
"FEHHHHEFHHIHFHIIIIHFIIJIJLMMLMLJIJIHFEFHHHHIHJIMMMMOMLLMLJIHHHHIJJIHHHHOMLLMLJLMOOMLJIMMMMOMLLMLJIHHHHLJJIHHHHIJLLJLJLMFJIHH",
//SONG 32
"QPOPQSSSSTSTUVVVVVVUTSTTSSSQPOQRQPPQPPQPPPOOOOPOOTUVVVVVVUTSSSQPOVVVVWWWVWXXWVVVVVWWSSXWVVVVVWWWWVUVTTUTUVVVWVWXXWXV",
//SONG 33
"LLJIHIJIIHFHFFELLJIHIJIIHFHFIJIKJIHHHHIHONMMLJIHHHHIHIJHHHIHONMMLOOMJHIJJIELJIHELJIHHONNMLMLJLHONNMLLOJIHJKJHFHFEELJIHELJIJIHHONNMLMLJLHONNMLLOJIHJKJHFHKJHFHIH",
//SONG 34
"MOMOMLMMOMOLMPQOPSQPQOPQOPMOPMOLMOPOMLMOLMOMLMOPOMLMOLMPQSPQTQTSRQSQPQQSTUTSQQSTUSTUTUTSQSTUTSQSPQPOPSRQSPPQSTQSQPOMPOMOPQNNQPNMMOMLMMOMLMQSPQT",
//SONG 35
"JLMLMNLJLLLLKKKJIHJKKKJIHJHIHJIJIHIJLMLMNLJLLLLKKKJIHJKKKJIHJLOPQPOQOPOMQPOPQQPOOOLOPQNNNLNOPQQRQOPQPOOOLOPQNNNLNOPQQMLRQOLQPOOOONOLJMQPOOOONOLJM",
//SONG 36
"MNOKLOLHIJKJIHJHKLOKLOLHIJKONOSSONOQONOLQPMNOPONOSSTUVSQRQMPOOVUTQPLUTSPOPQRRTSQPQQRSOVUTRUVWSWUVTUVTUVWS",
//SONG 37
"QPQPQPOMOPPQPOMOLQPQPQPOMOPPQPOMOPQPQPQPOMOPPQPOMOLQSSSTSQPQPPQPOMOOSSTVUUTQPQQSTTMQPQSSQSVUTUQTTUTSQPLMO",
//SONG 38
"SSSSQOPQOOMOPQOMLSSSSQOPQOOMOPQOMPMOOOPQQPQRQPOOMQMOOOPPQQPQRQPOOMSSQSTSOPQOVWVTQSTSTVTSQQQPQSQPOQPSQSTSOPQOVWVTQSTSTVTSQQPQSQPOMO",
//SONG 39
"EHIJKJHIHFHEHIJJKLHKJLIJIJLONMMLLMNMLJKKLMLKJIGGFEFHOMKLMNNNNMLJOMKLMFFFMKJIEHIJKJHHIIIIHFFGGFEMLIIKKKJIH",
//SONG 40
"EHHJMJLLMLJKJIFIIKNNMLKKJFGHIEHHJMJLLMLJKJIFIIKNNMLKKJFGIHMMLKLMLIJKILMLKINMLMLKLMJIH",
//SONG 41
"EHHHEGGGEHHHEIIIEHHHEGGGEHHHEIIIEKKKKKJJKKKLJIHGGHELLLLLKKLLLLLKKJJIEKKKKKJJKKKLJIHGGIHFHLMHLLLLLKKJJIHONOOLLLLKKJHONOOLLLLPPOHONONMHNMNMLHMLMLKKJKLMMLHONOOLLLLKKJHONOOLLLLPPOHONONMHNMNMLHMLMLKKJKLMMLHLHKJHHLHKJH"
// END
};
#endif
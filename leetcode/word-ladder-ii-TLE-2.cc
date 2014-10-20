#include <algorithm>
#include <iostream>

#include <string>
#include <vector>
using std::vector;
using std::string;

#include <unordered_set>
#include <unordered_map>
using std::unordered_set;
using std::unordered_map;

typedef unordered_set<string> HashSet;
typedef unordered_map<string, int> HashMap;
typedef unordered_map<string, vector<vector<string> > > PathCache;

HashSet visit;
HashMap wordId;
PathCache pathCache;
vector<vector<int> > minCost;
const int INF_MAX = std::numeric_limits<int>::max();

#ifdef __LOCAL_DEBUG__
#include <sys/time.h>
long now() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}
#endif

class Solution {
public:
    vector<vector<string> > findLadders(string start, string end, HashSet& dict) {
        vector<vector<string> > result;
        if (start == end) {
            vector<string> v;
            v.push_back(start), v.push_back(end);
            result.push_back(v);
            return result;
        }

        // assign id
        wordId.clear(), minCost.clear();
        int index = 0, wordCount = dict.size();
        for (HashSet::iterator pos = dict.begin(); pos != dict.end(); ++pos) {
            wordId[*pos] = index;
            vector<int> v(wordCount, INF_MAX);
            v[index++] = 0;
            minCost.push_back(v);
        }

        // build graph
        string temp;
        int word1, word2;
        HashSet::iterator pos;
        for (pos = dict.begin(); pos != dict.end(); ++pos) {
            temp = *pos;
            word1 = wordId[*pos];
            for (int i = 0; i < pos->size(); ++i) {
                for (int j = 0; j < 26; ++j) {
                    temp[i] = 'a' + j;
                    if (temp != *pos && dict.find(temp) != dict.end()) {
                        word2 = wordId[temp];
                        minCost[word1][word2] = 1;
                        minCost[word2][word1] = 1;
                    }
                    temp[i] = (*pos)[i];
                }
            }
        }

#ifdef __LOCAL_DEBUG__
        long st = now();
#endif
        // run Floyd-Warshall
        for (int k = 0; k < wordCount; ++k) {
            for (int i = 0; i < wordCount; ++i) {
                for (int j = 0; j < wordCount; ++j) {
                    if (minCost[i][k] != INF_MAX && minCost[k][j] != INF_MAX
                            && minCost[i][j] > minCost[i][k] + minCost[k][j]) {
                        minCost[i][j] = minCost[i][k] + minCost[k][j];
                    }
                }
            }
        }
#ifdef __LOCAL_DEBUG__
        std::cout << "run Floyd-Warshall cost " << now() - st << " ms\n";
#endif
        // Find all possible start/end node
        vector<string> adjStart;
        getAdjacencies(start, adjStart, dict);
        vector<string> adjEnd;
        getAdjacencies(end, adjEnd, dict);

        // find minPath
        int minPath = std::numeric_limits<int>::max();
        for (int i = 0; i < adjStart.size(); ++i) {
            word1 = wordId[adjStart[i]];
            for (int j = 0; j < adjEnd.size(); ++j) {
                word2 = wordId[adjEnd[j]];
                minPath = std::min(minPath, minCost[word1][word2]);
            }
        }

#ifdef __LOCAL_DEBUG__
        st = now();
#endif
        pathCache.clear();
        for (int i = 0; i < adjStart.size(); ++i) {
            word1 = wordId[adjStart[i]];
            for (int j = 0; j < adjEnd.size(); ++j) {
                word2 = wordId[adjEnd[j]];
                if (minCost[word1][word2] == minPath) {
                    visit.clear();
                    visit.insert(adjStart[i]);
                    vector<vector<string> > paths = getPaths(adjStart[i], adjEnd[j], minPath);
                    visit.erase(adjStart[i]);
                    for (int k = 0; k < paths.size(); ++k) {
                        paths[k].insert(paths[k].begin(), start);
                        paths[k].push_back(end);
                        result.push_back(paths[k]);
                    }
                }
            }
        }
#ifdef __LOCAL_DEBUG__
        std::cout << "run DFS cost " << now() - st << " ms\n";
#endif
        return result;
    }
private:
    void getAdjacencies(string& word, vector<string>& adj, HashSet& dict) {
        string temp = word;
        for (int i = 0; i < word.size(); ++i) {
            for (int j = 0; j < 26; ++j) {
                temp[i] = 'a' + j;
                if (temp != word && dict.find(temp) != dict.end()) {
                    adj.push_back(temp);
                }
                temp[i] = word[i];
            }
        }
    }

    vector<vector<string> > getPaths(string& curr, string& dest, int minPath) {
        if (pathCache.find(curr) != pathCache.end()) {
            return pathCache[curr];
        }

        //printf("curr: %s, dest: %s\n", curr.c_str(), dest.c_str());
        vector<vector<string> > paths;
        if (curr == dest) {
            vector<string> v;
            v.push_back(curr);
            paths.push_back(v);
            return paths;
        }
        int currId = wordId[curr], destId = wordId[dest], nextId;
        for (int i = 0; i < curr.size(); ++i) {
            for (int j = 0; j < 26; ++j) {
                string temp(curr);
                temp[i] = 'a' + j;
                if (wordId.find(temp) == wordId.end() // not exists
                        || visit.find(temp) != visit.end()) { // already used
                    continue;
                }

                nextId = wordId[temp];
                if (minCost[currId][nextId] + minCost[nextId][destId] != minPath) {
                    continue;
                }

                visit.insert(temp);
                vector<vector<string> > subpaths = getPaths(temp, dest,
                        minPath - minCost[currId][nextId]);
                visit.erase(temp);
                for (int i = 0; i < subpaths.size(); ++i) {
                    subpaths[i].insert(subpaths[i].begin(), curr);
                    paths.push_back(subpaths[i]);
                }
            }
        }

        pathCache[curr] = paths;
        return paths;
    }
};

Solution solu;

int main() {
    vector<vector<string> > result;
    unordered_set<string> dict;
    dict.insert("hot"), dict.insert("dot"), dict.insert("dog");
    dict.insert("lot"), dict.insert("log");

    result = solu.findLadders("hit", "cog", dict);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(),
                std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    result = solu.findLadders("hit", "got", dict);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(),
                std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    result = solu.findLadders("hit", "hit", dict);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(),
                std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    dict.clear();
    dict.insert("kid"), dict.insert("tag"), dict.insert("pup"), dict.insert("ail"), dict.insert(
            "tun"), dict.insert("woo"), dict.insert("erg"), dict.insert("luz"), dict.insert("brr"), dict.insert(
            "gay"), dict.insert("sip"), dict.insert("kay"), dict.insert("per"), dict.insert("val"), dict.insert(
            "mes"), dict.insert("ohs"), dict.insert("now"), dict.insert("boa"), dict.insert("cet"), dict.insert(
            "pal"), dict.insert("bar"), dict.insert("die"), dict.insert("war"), dict.insert("hay"), dict.insert(
            "eco"), dict.insert("pub"), dict.insert("lob"), dict.insert("rue"), dict.insert("fry"), dict.insert(
            "lit"), dict.insert("rex"), dict.insert("jan"), dict.insert("cot"), dict.insert("bid"), dict.insert(
            "ali"), dict.insert("pay"), dict.insert("col"), dict.insert("gum"), dict.insert("ger"), dict.insert(
            "row"), dict.insert("won"), dict.insert("dan"), dict.insert("rum"), dict.insert("fad"), dict.insert(
            "tut"), dict.insert("sag"), dict.insert("yip"), dict.insert("sui"), dict.insert("ark"), dict.insert(
            "has"), dict.insert("zip"), dict.insert("fez"), dict.insert("own"), dict.insert("ump"), dict.insert(
            "dis"), dict.insert("ads"), dict.insert("max"), dict.insert("jaw"), dict.insert("out"), dict.insert(
            "btu"), dict.insert("ana"), dict.insert("gap"), dict.insert("cry"), dict.insert("led"), dict.insert(
            "abe"), dict.insert("box"), dict.insert("ore"), dict.insert("pig"), dict.insert("fie"), dict.insert(
            "toy"), dict.insert("fat"), dict.insert("cal"), dict.insert("lie"), dict.insert("noh"), dict.insert(
            "sew"), dict.insert("ono"), dict.insert("tam"), dict.insert("flu"), dict.insert("mgm"), dict.insert(
            "ply"), dict.insert("awe"), dict.insert("pry"), dict.insert("tit"), dict.insert("tie"), dict.insert(
            "yet"), dict.insert("too"), dict.insert("tax"), dict.insert("jim"), dict.insert("san"), dict.insert(
            "pan"), dict.insert("map"), dict.insert("ski"), dict.insert("ova"), dict.insert("wed"), dict.insert(
            "non"), dict.insert("wac"), dict.insert("nut"), dict.insert("why"), dict.insert("bye"), dict.insert(
            "lye"), dict.insert("oct"), dict.insert("old"), dict.insert("fin"), dict.insert("feb"), dict.insert(
            "chi"), dict.insert("sap"), dict.insert("owl"), dict.insert("log"), dict.insert("tod"), dict.insert(
            "dot"), dict.insert("bow"), dict.insert("fob"), dict.insert("for"), dict.insert("joe"), dict.insert(
            "ivy"), dict.insert("fan"), dict.insert("age"), dict.insert("fax"), dict.insert("hip"), dict.insert(
            "jib"), dict.insert("mel"), dict.insert("hus"), dict.insert("sob"), dict.insert("ifs"), dict.insert(
            "tab"), dict.insert("ara"), dict.insert("dab"), dict.insert("jag"), dict.insert("jar"), dict.insert(
            "arm"), dict.insert("lot"), dict.insert("tom"), dict.insert("sax"), dict.insert("tex"), dict.insert(
            "yum"), dict.insert("pei"), dict.insert("wen"), dict.insert("wry"), dict.insert("ire"), dict.insert(
            "irk"), dict.insert("far"), dict.insert("mew"), dict.insert("wit"), dict.insert("doe"), dict.insert(
            "gas"), dict.insert("rte"), dict.insert("ian"), dict.insert("pot"), dict.insert("ask"), dict.insert(
            "wag"), dict.insert("hag"), dict.insert("amy"), dict.insert("nag"), dict.insert("ron"), dict.insert(
            "soy"), dict.insert("gin"), dict.insert("don"), dict.insert("tug"), dict.insert("fay"), dict.insert(
            "vic"), dict.insert("boo"), dict.insert("nam"), dict.insert("ave"), dict.insert("buy"), dict.insert(
            "sop"), dict.insert("but"), dict.insert("orb"), dict.insert("fen"), dict.insert("paw"), dict.insert(
            "his"), dict.insert("sub"), dict.insert("bob"), dict.insert("yea"), dict.insert("oft"), dict.insert(
            "inn"), dict.insert("rod"), dict.insert("yam"), dict.insert("pew"), dict.insert("web"), dict.insert(
            "hod"), dict.insert("hun"), dict.insert("gyp"), dict.insert("wei"), dict.insert("wis"), dict.insert(
            "rob"), dict.insert("gad"), dict.insert("pie"), dict.insert("mon"), dict.insert("dog"), dict.insert(
            "bib"), dict.insert("rub"), dict.insert("ere"), dict.insert("dig"), dict.insert("era"), dict.insert(
            "cat"), dict.insert("fox"), dict.insert("bee"), dict.insert("mod"), dict.insert("day"), dict.insert(
            "apr"), dict.insert("vie"), dict.insert("nev"), dict.insert("jam"), dict.insert("pam"), dict.insert(
            "new"), dict.insert("aye"), dict.insert("ani"), dict.insert("and"), dict.insert("ibm"), dict.insert(
            "yap"), dict.insert("can"), dict.insert("pyx"), dict.insert("tar"), dict.insert("kin"), dict.insert(
            "fog"), dict.insert("hum"), dict.insert("pip"), dict.insert("cup"), dict.insert("dye"), dict.insert(
            "lyx"), dict.insert("jog"), dict.insert("nun"), dict.insert("par"), dict.insert("wan"), dict.insert(
            "fey"), dict.insert("bus"), dict.insert("oak"), dict.insert("bad"), dict.insert("ats"), dict.insert(
            "set"), dict.insert("qom"), dict.insert("vat"), dict.insert("eat"), dict.insert("pus"), dict.insert(
            "rev"), dict.insert("axe"), dict.insert("ion"), dict.insert("six"), dict.insert("ila"), dict.insert(
            "lao"), dict.insert("mom"), dict.insert("mas"), dict.insert("pro"), dict.insert("few"), dict.insert(
            "opt"), dict.insert("poe"), dict.insert("art"), dict.insert("ash"), dict.insert("oar"), dict.insert(
            "cap"), dict.insert("lop"), dict.insert("may"), dict.insert("shy"), dict.insert("rid"), dict.insert(
            "bat"), dict.insert("sum"), dict.insert("rim"), dict.insert("fee"), dict.insert("bmw"), dict.insert(
            "sky"), dict.insert("maj"), dict.insert("hue"), dict.insert("thy"), dict.insert("ava"), dict.insert(
            "rap"), dict.insert("den"), dict.insert("fla"), dict.insert("auk"), dict.insert("cox"), dict.insert(
            "ibo"), dict.insert("hey"), dict.insert("saw"), dict.insert("vim"), dict.insert("sec"), dict.insert(
            "ltd"), dict.insert("you"), dict.insert("its"), dict.insert("tat"), dict.insert("dew"), dict.insert(
            "eva"), dict.insert("tog"), dict.insert("ram"), dict.insert("let"), dict.insert("see"), dict.insert(
            "zit"), dict.insert("maw"), dict.insert("nix"), dict.insert("ate"), dict.insert("gig"), dict.insert(
            "rep"), dict.insert("owe"), dict.insert("ind"), dict.insert("hog"), dict.insert("eve"), dict.insert(
            "sam"), dict.insert("zoo"), dict.insert("any"), dict.insert("dow"), dict.insert("cod"), dict.insert(
            "bed"), dict.insert("vet"), dict.insert("ham"), dict.insert("sis"), dict.insert("hex"), dict.insert(
            "via"), dict.insert("fir"), dict.insert("nod"), dict.insert("mao"), dict.insert("aug"), dict.insert(
            "mum"), dict.insert("hoe"), dict.insert("bah"), dict.insert("hal"), dict.insert("keg"), dict.insert(
            "hew"), dict.insert("zed"), dict.insert("tow"), dict.insert("gog"), dict.insert("ass"), dict.insert(
            "dem"), dict.insert("who"), dict.insert("bet"), dict.insert("gos"), dict.insert("son"), dict.insert(
            "ear"), dict.insert("spy"), dict.insert("kit"), dict.insert("boy"), dict.insert("due"), dict.insert(
            "sen"), dict.insert("oaf"), dict.insert("mix"), dict.insert("hep"), dict.insert("fur"), dict.insert(
            "ada"), dict.insert("bin"), dict.insert("nil"), dict.insert("mia"), dict.insert("ewe"), dict.insert(
            "hit"), dict.insert("fix"), dict.insert("sad"), dict.insert("rib"), dict.insert("eye"), dict.insert(
            "hop"), dict.insert("haw"), dict.insert("wax"), dict.insert("mid"), dict.insert("tad"), dict.insert(
            "ken"), dict.insert("wad"), dict.insert("rye"), dict.insert("pap"), dict.insert("bog"), dict.insert(
            "gut"), dict.insert("ito"), dict.insert("woe"), dict.insert("our"), dict.insert("ado"), dict.insert(
            "sin"), dict.insert("mad"), dict.insert("ray"), dict.insert("hon"), dict.insert("roy"), dict.insert(
            "dip"), dict.insert("hen"), dict.insert("iva"), dict.insert("lug"), dict.insert("asp"), dict.insert(
            "hui"), dict.insert("yak"), dict.insert("bay"), dict.insert("poi"), dict.insert("yep"), dict.insert(
            "bun"), dict.insert("try"), dict.insert("lad"), dict.insert("elm"), dict.insert("nat"), dict.insert(
            "wyo"), dict.insert("gym"), dict.insert("dug"), dict.insert("toe"), dict.insert("dee"), dict.insert(
            "wig"), dict.insert("sly"), dict.insert("rip"), dict.insert("geo"), dict.insert("cog"), dict.insert(
            "pas"), dict.insert("zen"), dict.insert("odd"), dict.insert("nan"), dict.insert("lay"), dict.insert(
            "pod"), dict.insert("fit"), dict.insert("hem"), dict.insert("joy"), dict.insert("bum"), dict.insert(
            "rio"), dict.insert("yon"), dict.insert("dec"), dict.insert("leg"), dict.insert("put"), dict.insert(
            "sue"), dict.insert("dim"), dict.insert("pet"), dict.insert("yaw"), dict.insert("nub"), dict.insert(
            "bit"), dict.insert("bur"), dict.insert("sid"), dict.insert("sun"), dict.insert("oil"), dict.insert(
            "red"), dict.insert("doc"), dict.insert("moe"), dict.insert("caw"), dict.insert("eel"), dict.insert(
            "dix"), dict.insert("cub"), dict.insert("end"), dict.insert("gem"), dict.insert("off"), dict.insert(
            "yew"), dict.insert("hug"), dict.insert("pop"), dict.insert("tub"), dict.insert("sgt"), dict.insert(
            "lid"), dict.insert("pun"), dict.insert("ton"), dict.insert("sol"), dict.insert("din"), dict.insert(
            "yup"), dict.insert("jab"), dict.insert("pea"), dict.insert("bug"), dict.insert("gag"), dict.insert(
            "mil"), dict.insert("jig"), dict.insert("hub"), dict.insert("low"), dict.insert("did"), dict.insert(
            "tin"), dict.insert("get"), dict.insert("gte"), dict.insert("sox"), dict.insert("lei"), dict.insert(
            "mig"), dict.insert("fig"), dict.insert("lon"), dict.insert("use"), dict.insert("ban"), dict.insert(
            "flo"), dict.insert("nov"), dict.insert("jut"), dict.insert("bag"), dict.insert("mir"), dict.insert(
            "sty"), dict.insert("lap"), dict.insert("two"), dict.insert("ins"), dict.insert("con"), dict.insert(
            "ant"), dict.insert("net"), dict.insert("tux"), dict.insert("ode"), dict.insert("stu"), dict.insert(
            "mug"), dict.insert("cad"), dict.insert("nap"), dict.insert("gun"), dict.insert("fop"), dict.insert(
            "tot"), dict.insert("sow"), dict.insert("sal"), dict.insert("sic"), dict.insert("ted"), dict.insert(
            "wot"), dict.insert("del"), dict.insert("imp"), dict.insert("cob"), dict.insert("way"), dict.insert(
            "ann"), dict.insert("tan"), dict.insert("mci"), dict.insert("job"), dict.insert("wet"), dict.insert(
            "ism"), dict.insert("err"), dict.insert("him"), dict.insert("all"), dict.insert("pad"), dict.insert(
            "hah"), dict.insert("hie"), dict.insert("aim"), dict.insert("ike"), dict.insert("jed"), dict.insert(
            "ego"), dict.insert("mac"), dict.insert("baa"), dict.insert("min"), dict.insert("com"), dict.insert(
            "ill"), dict.insert("was"), dict.insert("cab"), dict.insert("ago"), dict.insert("ina"), dict.insert(
            "big"), dict.insert("ilk"), dict.insert("gal"), dict.insert("tap"), dict.insert("duh"), dict.insert(
            "ola"), dict.insert("ran"), dict.insert("lab"), dict.insert("top"), dict.insert("gob"), dict.insert(
            "hot"), dict.insert("ora"), dict.insert("tia"), dict.insert("kip"), dict.insert("han"), dict.insert(
            "met"), dict.insert("hut"), dict.insert("she"), dict.insert("sac"), dict.insert("fed"), dict.insert(
            "goo"), dict.insert("tee"), dict.insert("ell"), dict.insert("not"), dict.insert("act"), dict.insert(
            "gil"), dict.insert("rut"), dict.insert("ala"), dict.insert("ape"), dict.insert("rig"), dict.insert(
            "cid"), dict.insert("god"), dict.insert("duo"), dict.insert("lin"), dict.insert("aid"), dict.insert(
            "gel"), dict.insert("awl"), dict.insert("lag"), dict.insert("elf"), dict.insert("liz"), dict.insert(
            "ref"), dict.insert("aha"), dict.insert("fib"), dict.insert("oho"), dict.insert("tho"), dict.insert(
            "her"), dict.insert("nor"), dict.insert("ace"), dict.insert("adz"), dict.insert("fun"), dict.insert(
            "ned"), dict.insert("coo"), dict.insert("win"), dict.insert("tao"), dict.insert("coy"), dict.insert(
            "van"), dict.insert("man"), dict.insert("pit"), dict.insert("guy"), dict.insert("foe"), dict.insert(
            "hid"), dict.insert("mai"), dict.insert("sup"), dict.insert("jay"), dict.insert("hob"), dict.insert(
            "mow"), dict.insert("jot"), dict.insert("are"), dict.insert("pol"), dict.insert("arc"), dict.insert(
            "lax"), dict.insert("aft"), dict.insert("alb"), dict.insert("len"), dict.insert("air"), dict.insert(
            "pug"), dict.insert("pox"), dict.insert("vow"), dict.insert("got"), dict.insert("meg"), dict.insert(
            "zoe"), dict.insert("amp"), dict.insert("ale"), dict.insert("bud"), dict.insert("gee"), dict.insert(
            "pin"), dict.insert("dun"), dict.insert("pat"), dict.insert("ten"), dict.insert("mob");

    result = solu.findLadders("cet", "ism", dict);
    for (int i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(),
                std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}


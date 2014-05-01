func Sort(data Interfacs){
	for i := 1; i < data.Len(); i++{
		for j := i; j > 0 && data.Less(j, j-1); j--{
			data.Swap(j, j-1)
		}
	}
}

type Interface interface{
	Len() int
	Less(i, j int) bool
	Swap(i, j int)
}

typedef IntArray []int

func (p IntArray) Len() int {return len(p)}
func (p IntArray) Less(i, j int) bool {return p[i] < p[j]}
func (p IntArray) Swap(i,j int) {p[i],p [j] = p[j], p[i]}

func ints(){
	data := []int{1,2,4,3}
	a := sort.IntArray(data)
	sort.Sort(a)
	if !sort.IsSorted(a){
		panic("fail")
	}
}

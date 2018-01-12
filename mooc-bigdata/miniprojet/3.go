package main

import (
	"encoding/csv"
	"fmt"
	"github.com/gonum/matrix/mat64"
	"log"
	"os"
	"strconv"
)

func main() {

	nbcol := 11
	nbline := 4898
	y := mat64.NewDense(nbline, 1, nil)
	z := mat64.NewDense(nbline, nbcol, nil)

	file, err := os.Open("./winequality-white.csv")
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	r := csv.NewReader(file)
	r.Comma = ';'
	r.Comment = '#'
	lines, _ := r.ReadAll()
	for i, line := range lines {
		for j, val := range line {
			val, err := strconv.ParseFloat(val, 64)
			if err != nil {
				log.Fatal(err)
			}
			if j < 11 {
				z.Set(i, j, val)
			} else {
				y.Set(i, 0, val)
			}
		}
	}

	//fmt.Printf("Z\n")
	//printmat(z)

	xt := z.T()
	//fmt.Printf("xt\n")
	//printmat(xt)

	xtx := mat64.NewDense(nbcol, nbcol, nil)
	xtx.Mul(xt, z)
	//fmt.Printf("xtx\n")
	//printmat(xtx)

	xtxinv := mat64.NewDense(nbcol, nbcol, nil)
	xtxinv.Inverse(xtx)
	//fmt.Printf("xtxinv\n")
	//printmat(xtxinv)

	identity := mat64.NewDense(nbcol, nbcol, nil)
	identity.Mul(xtx, xtxinv)
	fmt.Printf("Check id\n")
	printmat(identity)

	xtxinvxt := mat64.NewDense(nbcol, nbline, nil)
	xtxinvxt.Mul(xtxinv, xt)
	//fmt.Printf("xtxinvxt\n")
	//printmat(xtxinvxt)

	fmt.Printf("y\n")
	printmat(y)
	beta := mat64.NewDense(nbcol, 1, nil)
	beta.Mul(xtxinvxt, y)
	fmt.Printf("beta\n")
	printmat(beta)

}

func printmat(x mat64.Matrix) {
	fmt.Printf("%v\n", mat64.Formatted(x, mat64.Prefix(""), mat64.Squeeze()))
}

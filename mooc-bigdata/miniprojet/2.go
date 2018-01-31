package main

import (
	"fmt"
	"github.com/gonum/matrix/mat64"
)

func main() {

	dim := 8
	data := []float64{1, 1, 1, 1, 1, 1, 1, 1}
	y := mat64.NewDense(dim, 1, data)
	fmt.Printf("y\n")
	printmat(y)

	// pass the slice dx as data to the matrix x
	x := mat64.NewDense(dim, dim, nil)
	for i := 0; i < dim; i++ {
		x.Set(i, i, 1.)
	}

	id8 := mat64.NewDense(dim, dim, nil)
	id8.Copy(x)

	x.Set(0, dim-1, 1.)
	fmt.Printf("x\n")
	printmat(x)

	xt := x.T()
	fmt.Printf("xt\n")
	printmat(xt)

	xtx := mat64.NewDense(dim, dim, nil)
	xtx.Mul(xt, x)
	fmt.Printf("xtx\n")
	printmat(xtx)

	sub := mat64.NewDense(dim, dim, nil)
	sub.Sub(xtx, id8)
	fmt.Printf("Sub\n")
	printmat(sub)

	var eigen mat64.Eigen
	eigen.Factorize(sub, false, false)
	values := eigen.Values(nil)
	fmt.Printf("Eigen values: %v\n", values)
}

func printmat(x mat64.Matrix) {
	fmt.Printf("%v\n", mat64.Formatted(x, mat64.Prefix(""), mat64.Squeeze()))
}

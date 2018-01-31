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

	xtxinv := mat64.NewDense(dim, dim, nil)
	xtxinv.Inverse(xtx)
	fmt.Printf("xtxinv\n")
	printmat(xtxinv)

	identity := mat64.NewDense(dim, dim, nil)
	identity.Mul(xtx, xtxinv)
	fmt.Printf("Check id\n")
	printmat(identity)

	xtxinvxt := mat64.NewDense(dim, dim, nil)
	xtxinvxt.Mul(xtxinv, xt)
	fmt.Printf("xtxinvxt\n")
	printmat(xtxinvxt)

	beta := mat64.NewDense(dim, 1, nil)
	beta.Mul(xtxinvxt, y)
	fmt.Printf("beta\n")
	printmat(beta)
}

func printmat(x mat64.Matrix) {
	fmt.Printf("%v\n", mat64.Formatted(x, mat64.Prefix(""), mat64.Squeeze()))
}

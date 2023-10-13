// Create a golang program which count number of pod in kube-system namespace
// and print the result to console
// Use kubernetes go-client library

package main

import (
	"context"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"time"

	metav1 "k8s.io/apimachinery/pkg/apis/meta/v1"
	"k8s.io/client-go/kubernetes"
	"k8s.io/client-go/tools/clientcmd"
)

// Create a function which create a Kubernetes clientset from kubeconfig file
// and return the clientset
func createClientset() (*kubernetes.Clientset, error) {
	// Get kubeconfig file path from environment variable
	kubeconfig := os.Getenv("KUBECONFIG")
	if kubeconfig == "" {
		return nil, fmt.Errorf("KUBECONFIG environment variable is not set")
	}

	// Get absolute path of kubeconfig file
	kubeconfig, err := filepath.Abs(kubeconfig)
	if err != nil {
		return nil, err
	}

	// Build config from kubeconfig file
	config, err := clientcmd.BuildConfigFromFlags("", kubeconfig)
	if err != nil {
		return nil, err
	}

	// Create kubernetes clientset
	clientset, err := kubernetes.NewForConfig(config)
	if err != nil {
		return nil, err
	}

	return clientset, nil
}

// Create a factorial function
func factorial(n int) int {
	if n == 0 {
		return 1
	}
	return n * factorial(n-1)
}

// Create a fibonacci function
func fibonacci(n int) int {
	if n <= 1 {
		return n
	}
	return fibonacci(n-1) + fibonacci(n-2)
}

func main() {
	// Get kubeconfig file path from environment variable
	kubeconfig := os.Getenv("KUBECONFIG")
	if kubeconfig == "" {
		log.Fatal("KUBECONFIG environment variable is not set")
	}

	// Get absolute path of kubeconfig file
	kubeconfig, err := filepath.Abs(kubeconfig)
	if err != nil {
		log.Fatal(err)
	}

	// Build config from kubeconfig file
	config, err := clientcmd.BuildConfigFromFlags("", kubeconfig)
	if err != nil {
		log.Fatal(err)
	}

	// Create kubernetes clientset
	clientset, err := kubernetes.NewForConfig(config)
	if err != nil {
		log.Fatal(err)
	}

	// Create context with timeout
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Get pods in kube-system namespace
	pods, err := clientset.CoreV1().Pods("kube-system").List(ctx, metav1.ListOptions{})
	if err != nil {
		log.Fatal(err)
	}

	// Print number of pods
	fmt.Printf("Number of pods in kube-system namespace: %d\n", len(pods.Items))
}

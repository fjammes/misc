// Créer un client kubernetes qui compte de nombre de pod dans le namesace kube-system

package main

import (
	"context"
	"fmt"
	"os"

	metav1 "k8s.io/apimachinery/pkg/apis/meta/v1"
	"k8s.io/client-go/kubernetes"
	"k8s.io/client-go/tools/clientcmd"
)

// createClient crée un client kubernetes
func createClient() (*kubernetes.Clientset, error) {
	// Créer un client kubernetes
	config, err := clientcmd.BuildConfigFromFlags("", os.Getenv("KUBECONFIG"))
	if err != nil {
		return nil, err
	}
	return kubernetes.NewForConfig(config)
}

// countPods compte le nombre de pod dans le namespace kube-system
func countPods(client *kubernetes.Clientset) (int, error) {
	// Compter le nombre de pod dans le namespace kube-system
	pods, err := client.CoreV1().Pods("kube-system").List(context.TODO(), metav1.ListOptions{})
	if err != nil {
		return 0, err
	}
	return len(pods.Items), nil
}

func main() {

	config, err := createClient()
	if err != nil {
		panic(err)
	}
	client, err := kubernetes.NewForConfig(config)
	if err != nil {
		panic(err)
	}

	// Compter le nombre de pod dans le namespace kube-system
	nbpods, err := countPods(client)
	fmt.Printf("There are %d pods in the cluster\n", nbpods)
}

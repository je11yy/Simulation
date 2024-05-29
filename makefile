all: info_file_generator

main: main.c validation.c errors.c logger.c application.c storages/department_storage.c storages/application_storage.c storages/departments/department.c storages/departments/BinarySearchTree.c storages/departments/DynamicArray.c storages/departments/HashSet.c storages/departments/Trie.c storages/applications/BinaryHeap.c storages/applications/BinomialHeap.c storages/applications/FibonacciHeap.c storages/applications/LeftistHeap.c storages/applications/SkewHeap.c storages/applications/Treap.c
	gcc main.c validation.c errors.c logger.c application.c storages/department_storage.c storages/application_storage.c storages/departments/department.c storages/departments/BinarySearchTree.c storages/departments/DynamicArray.c storages/departments/HashSet.c storages/departments/Trie.c storages/applications/BinaryHeap.c storages/applications/BinomialHeap.c storages/applications/FibonacciHeap.c storages/applications/LeftistHeap.c storages/applications/SkewHeap.c storages/applications/Treap.c -o main -lm

applications_generator: errors.c applications_generator.c
	gcc errors.c applications_generator.c -o applications_generator

info_file_generator: info_file_generator.c validation.c errors.c logger.c application.c storages/department_storage.c storages/application_storage.c storages/departments/department.c storages/departments/BinarySearchTree.c storages/departments/DynamicArray.c storages/departments/HashSet.c storages/departments/Trie.c storages/applications/BinaryHeap.c storages/applications/BinomialHeap.c storages/applications/FibonacciHeap.c storages/applications/LeftistHeap.c storages/applications/SkewHeap.c storages/applications/Treap.c
	gcc info_file_generator.c validation.c errors.c logger.c application.c storages/department_storage.c storages/application_storage.c storages/departments/department.c storages/departments/BinarySearchTree.c storages/departments/DynamicArray.c storages/departments/HashSet.c storages/departments/Trie.c storages/applications/BinaryHeap.c storages/applications/BinomialHeap.c storages/applications/FibonacciHeap.c storages/applications/LeftistHeap.c storages/applications/SkewHeap.c storages/applications/Treap.c -o info_file_generator -lm

clean:
	rm -rf *.o main applications_generator info_file_generator
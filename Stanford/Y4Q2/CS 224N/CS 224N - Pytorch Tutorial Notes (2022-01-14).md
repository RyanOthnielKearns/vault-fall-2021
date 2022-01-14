#Stanford #Stanford-Winter-2022 #CS #CS224N #pytorch #tutorial
___
[Google Colab here](https://colab.research.google.com/drive/14dvzksNhr8xDxG0rh7K5okRpAosKSeT5#scrollTo=6XfnKI4-a5j9)
# Tensors
**tensor**, not matrix, because can have an arbitrary number of dimensions
- 2D tensor (matrix) initialized with a `list` of `list`s:
```
data = torch.tensor([
	[0, 1],
	[2, 3],
	[4, 5]
])
```
- **vectors** are just 1D tensors
- data is stored much more efficiently than a list of lists as far as the GPU is concerned
- cannot have *heterogenous* types -- all types converted to the same one
- **utility functions**, like `torch.zeros(d1, d2)` or `torch.ones(d1, d2)`, used to create tensors with given *shape* or *contents*

## Broadcasting
```
rr = torch.arange(1, 10) # range from [1, 10)
print(rr)
> tensor([1, 2, 3, 4, 5, 6, 7, 8, 9]) 

rr + 2
> tensor([ 3,  4,  5,  6,  7,  8,  9, 10, 11])
```
- in the above example `2` is broadcast to a 1x10 tensor

## Multiplying tensors
```
a = torch.tensor([[1, 2], [3, 4], [5, 6]])
b = torch.tensor([[1, 2, 3, 4], [5, 6, 7, 8]])
a.matmul(b) # or a @ b does the same thing

> tensor([
	[11, 14, 17, 20],
	[23, 30, 37, 44],
	[35, 46, 57, 68]
])
```

## Reshaping
`tensor.view(d1, d2)` can reshape into the dimensions you specify

## Vectorized Operations
running `tensor.sum()` with `dim` unspecified will result in flattening the tensor before taking the sum
- `dim=0` will sum over rows (the innermost nested collections of data)
- `dim=1` will sum over columns (the $i$th entry of each innermost nested collection...)
- etc.

## Slicing
- use comma notation `tensor[2, 0]` (instead of `tensor[2][0]`) to better make use of the `:` symbol (to catch everything from the given dimension)

## Automatic differentiation (autograd)
- use the `requires_grad=True` parameter to tell PyTorch to store gradients
- then can print gradient using `tensor.grad`
- then use `tensor.backward()` to compute gradients w.r.t. previous operations
	- when you call `.backward()` PyTorch will accumulate (sum) the gradient calculated to the gradients calculated so far
	- this is why it's so important to use `zero_grad()` when initializing an epoch of training

## Neural Networks
- data of shape `(2, 3, 4)` through a linear layer w/ shape `(4, 2)` -> output will be shape `(2, 3, 2)`
	- in general transforming `N,*,H_in` dimensional inputs to `N,*,H_out`
- probing the parameters of your model: checkout `model.named_parameters()`
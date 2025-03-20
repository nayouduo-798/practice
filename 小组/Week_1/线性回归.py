import numpy as np
# y = wx + b
#损失计算函数
def compute_error_for_line_given_points(b, w, points):
    totalError = 0
    for i in range(1, len(points)):#len(points)数据量
        x = points[i, 0:12]
        y = points[i, 12]
        # computer mean-squared-error
        totalError += (y - (np.matmul(w,x) + b)) ** 2  # 所有数据的损失和
    # average loss for each point
   # print(totalError)
    return totalError / float(len(points))
# 梯度计算函数
def step_gradient(b_current, w_current, points, learningRate):#w_current 矩阵
    b_gradient = 0
    w_gradient = np.array(np.zeros((1,12)))
    N = float(len(points))
    for i in range(1, len(points)):#i 控制行 j控制列
        for j in range(0,12):
            x = points[i,0:12]
            y = points[i, 12]
            # grad_b = 2(wx+b-y)
            b_gradient += (2 / N) * ((np.matmul(w_current,x) + b_current) - y)
            # grad_w = 2(wx+b-y)*x
            w_gradient[0,j] += (2 / N) * points[i, j] * ((np.matmul(w_current,x) + b_current) - y)
    # update w'
    new_b = b_current - (learningRate * b_gradient)
    new_w = w_current - (learningRate * w_gradient)
    return [new_b, new_w]


# 更新参数
def gradient_descent_runner(points, starting_b, starting_w, learning_rate, num_iterations):
    b = starting_b#矩阵
    w = starting_w
    # update for several times
    for i in range(num_iterations):  # 控制迭代次数
        b, w = step_gradient(b, w, np.array(points), learning_rate)
    return [b, w]


# 开始训练
def run():
    points = np.genfromtxt(r"C:\Users\LX\Desktop\boston_house_price_english.csv", delimiter=",")  # delimiter 分割符号
    learning_rate = 0.0001  # 学习率
    initial_b = 0  # initial y-intercept guess
    initial_w = np.array(np.zeros((1,12)))  # initial slope guess
    num_iterations = 1000  # 迭代次数
    for i in range(12):
        points[1:, i] = (points[1:, i] - points[1:, i].min()) / (points[1:, i].max() - points[1:, i].min())
    print("Starting gradient descent at b = {0}, w = {1}, error = {2}"
          .format(initial_b, initial_w,
                  compute_error_for_line_given_points(initial_b, initial_w, points))
          )  # 刚开始的w和b参数 以及初始损失
    print("Running...")
    [b, w] = gradient_descent_runner(points, initial_b, initial_w, learning_rate, num_iterations)
    print("After {0} iterations b = {1}, w = {2}, error = {3}".
          format(num_iterations, b, w,
                 compute_error_for_line_given_points(b, w, points))
          )


import warnings
# 忽略所有警告
warnings.filterwarnings("ignore")

if __name__ == '__main__':
    run()






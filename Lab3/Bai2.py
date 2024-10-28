from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/sensors', methods=['POST'])
def handle_sensors():
    data = request.get_json()
    # Xử lý dữ liệu từ cảm biến ở đây
    print(data)  # In dữ liệu để kiểm tra

    # Giả định rằng bạn quyết định số lượng LED sẽ bật
    led_count = 0
    if data['light'] < 200:  # Chỉ là ví dụ, điều chỉnh theo nhu cầu
        led_count = 3
    elif data['light'] < 400:
        led_count = 2
    else:
        led_count = 1

    return jsonify({
        "error": False,
        "message": "Data received successfully",
        "data": {
            "led_count": led_count
        }
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
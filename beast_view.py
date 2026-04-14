import requests

API_KEY = "YOUR_API_KEY"  # 换成你新生成的 key
CHANNEL_ID = "UCX6OQ3DkcsbYNE6H8uQQuVA"  # MrBeast

url = "https://youtube.googleapis.com/youtube/v3/channels"
params = {
    "part": "statistics",
    "id": CHANNEL_ID,
    "key": API_KEY,
}

resp = requests.get(url, params=params, timeout=15)
print(resp.status_code)
print(resp.text)

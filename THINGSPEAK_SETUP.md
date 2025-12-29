# ThingSpeak Setup Guide

This guide will walk you through setting up ThingSpeak cloud integration for real-time IoT monitoring.

## Step 1: Create ThingSpeak Account

1. Visit [ThingSpeak.com](https://thingspeak.com)
2. Click **Sign Up** (or **Get Started for Free**)
3. Create account using email or MathWorks account
4. Verify your email address

## Step 2: Create a New Channel

1. After logging in, click **Channels → My Channels**
2. Click **New Channel** button
3. Fill in channel details:

   **Channel Settings:**
   - **Name**: `Autonomous Robot Monitoring`
   - **Description**: `Real-time obstacle detection and distance monitoring for autonomous navigation system`

   **Field Configuration:**
   - **Field 1**: `Distance (cm)`
   - **Field 2**: `Obstacle Status`
   - Leave Fields 3-8 empty (not used)

4. Click **Save Channel**

## Step 3: Get Your API Credentials

### Write API Key (Required)

1. In your channel page, click **API Keys** tab
2. Locate **Write API Key** section
3. Copy the API key (format: `XXXXXXXXXXXXXXXX`)
4. Keep this key secure - it allows write access to your channel

### Channel ID (Required)

1. Look at your channel page URL:

   ```
   https://thingspeak.com/channels/1234567/private/show
                                    ^^^^^^^
                                  Channel ID
   ```

2. Note the Channel ID number

## Step 4: Update Arduino Code

Open `sketch.ino` and modify lines 36-37:

```cpp
// BEFORE:
unsigned long myChannelNumber = CHANNEL ID;
const char * myWriteAPIKey = "API KEY";

// AFTER (example):
unsigned long myChannelNumber = 1234567;
const char * myWriteAPIKey = "ABCDEFGHIJKLMNO0";
```

## Step 5: Verify Connection

1. Upload the code to ESP32
2. Open Serial Monitor (115200 baud)
3. Wait for WiFi connection
4. Look for confirmation message:

   ```
   >> ThingSpeak Update Successful.
   ```

### Troubleshooting Messages

| Message | Meaning | Solution |
|---------|---------|----------|
| `ThingSpeak Update Successful.` | ✅ Working correctly | No action needed |
| `ThingSpeak Error: 404` | ❌ Channel not found | Verify Channel ID |
| `ThingSpeak Error: 400` | ❌ Invalid API key | Check Write API Key |
| `ThingSpeak Error: -401` | ⚠️ No internet connection | Check WiFi settings |

## Step 6: View Live Data

1. Go to **Channels → My Channels → [Your Channel]**
2. You'll see two graphs:
   - **Field 1 Chart**: Real-time distance measurements
   - **Field 2 Chart**: Obstacle detection status (0=clear, 1=detected)

## Step 7: Customize Visualization (Optional)

### Add MATLAB Visualizations

1. Click **Apps → MATLAB Visualizations**
2. Create custom plots or analysis scripts

### Create Public View

1. Go to **Sharing** tab
2. Check **Share channel view with everyone**
3. Copy the public URL to share your data

### Set Up Alerts

1. Click **Apps → React**
2. Create conditions (e.g., "Alert me when obstacle detected")
3. Choose action: Email, ThingHTTP, or Tweet

## Update Frequency

The system updates ThingSpeak every **15 seconds** (configurable in code line 41):

```cpp
unsigned long timerDelay = 15000; // 15 seconds in milliseconds
```

**Note**: ThingSpeak free tier allows:

- 3 million messages/year
- 4 updates per minute
- 4 channels

## API Rate Limits

| Plan | Updates/Minute | Channels | Messages/Year |
|------|---------------|----------|---------------|
| Free | 4 | 4 | 3 million |
| Student | 10 | 4 | 33 million |
| Standard | 60 | 10 | 33 million |

## Example Data Views

After 15 minutes of operation, you should see:

- Distance values ranging from 0-400 cm
- Obstacle status toggling between 0 and 1
- Continuous data stream with 15-second intervals

---

✅ **Setup Complete!** Your robot is now connected to the cloud.

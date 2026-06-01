async function checkSystemMode() {
  try {
    const res = await fetch("./maintenance.json", { cache: "no-store" });
    const data = await res.json();

    if (!data || !data.active || !data[data.active]) {
      console.warn("Invalid maintenance.json, continuing normal mode");
      return;
    }

    const state = data[data.active];

    if (state.mode === "maintenance") {
      window.location.href = "maintenance.html?code=" + (state.code || "503");
      return;
    }

    if (state.mode === "degraded") {
      console.warn("Toollibs degraded mode:", state.code || "unknown");
    }

  } catch (e) {
    console.warn("Maintenance system unavailable, continuing normal mode");
  }
}

window.onerror = function(message) {
  console.error("Fatal error:", message);
  return false;
};

checkSystemMode();

async function registerDevice() {
  let deviceId = localStorage.getItem(
    "toollibs_device_id"
  );

  if (!deviceId) {
    deviceId = crypto.randomUUID();

    localStorage.setItem(
      "toollibs_device_id",
      deviceId
    );
  }

  try {
    await fetch(
      "http://192.168.1.19:3000/register-device",
      {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify({
          id: deviceId,
          platform: navigator.platform,
          arch: navigator.userAgent
        })
      }
    );
  } catch (e) {
    console.error("Counter unavailable");
  }
}

registerDevice();

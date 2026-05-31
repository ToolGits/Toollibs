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
async function checkSystemMode() {
  try {
    const res = await fetch("./maintenance.json", { cache: "no-store" });
    const data = await res.json();

    if (!data || !data.active || !data[data.active]) {
      console.warn("Invalid maintenance.json structure");
      return;
    }

    const state = data[data.active];

    if (state.mode === "maintenance") {
      const code = state.code || "503";
      window.location.href = "maintenance.html?code=" + code;
      return;
    }

    if (state.mode === "degraded") {
      console.warn("Toollibs degraded mode:", state.code || "unknown");
    }

  } catch (e) {
    console.error("Failed to check system mode", e);
  }
}

window.onerror = function(message, source, lineno, colno, error) {
  console.error("Fatal error detected:", message);

  fetch("./maintenance.json", { cache: "no-store" })
    .then(r => r.json())
    .then(data => {
      if (data && data.active && data[data.active]) {
        const state = data[data.active];

        if (state.mode !== "maintenance") {
          console.warn("System instability detected");
        }
      }
    })
    .catch(() => {
      console.error("Cannot fetch maintenance.json during error handling");
    });

  return false;
};

checkSystemMode();